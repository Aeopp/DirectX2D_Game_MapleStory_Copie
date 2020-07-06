#include "Mesh.h"

#include "D3DTexture.h"

namespace FramebufferShaders
{
#include "FramebufferVS.shh"
#include "FramebufferPS.shh"
};

Mesh::~Mesh()
{
	if (pRasterizerState) pRasterizerState->Release();
	if (pBlendState) pBlendState->Release();
	if (pSamplerState) pSamplerState->Release();
	if (pVertexBuffer) pVertexBuffer->Release();
	if (pVertexShader) pVertexShader->Release();
	if (pPixelShader) pPixelShader->Release();
	if (pInputLayout) pInputLayout->Release();
}

void Mesh::Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
{
	this->pDevice = pDevice;
	this->pImmediateContext = pImmediateContext;

	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth = sizeof(PCTVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0u;
	bd.Usage = D3D11_USAGE_DEFAULT;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;
	if (FAILED(pDevice->CreateBuffer(&bd, &initData, &pVertexBuffer)))
	{
		MessageBox(nullptr, L"Failed To Create Texture Vertex Buffer", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	bd.ByteWidth = sizeof(DWORD) * 6;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	DWORD indexes[6];
	indexes[0] = 0;
	indexes[1] = 1;
	indexes[2] = 2;
	indexes[3] = 2;
	indexes[4] = 1;
	indexes[5] = 3;
	initData.pSysMem = indexes;
	if (FAILED(pDevice->CreateBuffer(&bd, &initData, &pIndexBuffer)))
	{
		MessageBox(nullptr, L"Failed To Create Texture Index Buffer", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	initData.pSysMem = &cb;
	if (FAILED(pDevice->CreateBuffer(&bd, &initData, &pConstBuffer)))
	{
		MessageBox(nullptr, L"Failed To Create Texture Constant Buffer", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	if (FAILED(pDevice->CreateVertexShader(
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		nullptr,
		&pVertexShader)))
	{
		MessageBox(nullptr, L"Failed To Create Texture Vertex Shader", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	if (FAILED(pDevice->CreatePixelShader(
		FramebufferShaders::FramebufferPSBytecode,
		sizeof(FramebufferShaders::FramebufferPSBytecode),
		nullptr,
		&pPixelShader)))
	{
		MessageBox(nullptr, L"Failed To Create Texture Pixel Shader", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT nElement = sizeof(ied) / sizeof(ied[0]);
	if (FAILED(pDevice->CreateInputLayout(ied, nElement,
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		&pInputLayout)))
	{
		MessageBox(nullptr, L"Failed To Create Texture Layout", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(pDevice->CreateSamplerState(&sampDesc, &pSamplerState)))
	{
		MessageBox(nullptr, L"Failed To Create Texture SamplerState", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	D3D11_BLEND_DESC blendDesc = {};
	/*blendDesc.AlphaToCoverageEnable;
	blendDesc.IndependentBlendEnable;*/
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;

	if (FAILED(pDevice->CreateBlendState(&blendDesc, &pBlendState)))
	{
		MessageBox(nullptr, L"Failed To Create Texture BlendState", L"ERROR", MB_OK);
		PostQuitMessage(0);
	};

	D3D11_RASTERIZER_DESC rd = {};
	rd.FillMode = D3D11_FILL_SOLID;
	//rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.CullMode = D3D11_CULL_NONE;
	/*BOOL FrontCounterClockwise;
	INT DepthBias;
	FLOAT DepthBiasClamp;
	FLOAT SlopeScaledDepthBias;
	BOOL DepthClipEnable = false;
	BOOL ScissorEnable = false;
	BOOL MultisampleEnable = false;
	BOOL AntialiasedLineEnable = false;*/


	pImmediateContext->VSSetConstantBuffers(0u, 1u, &pConstBuffer);
	pImmediateContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0u);
	pImmediateContext->IASetInputLayout(pInputLayout);
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pImmediateContext->VSSetShader(pVertexShader, nullptr, 0u);
	pImmediateContext->PSSetShader(pPixelShader, nullptr, 0u);
	pImmediateContext->PSSetSamplers(0u, 1u, &pSamplerState);
	pImmediateContext->OMSetBlendState(pBlendState, nullptr, 0xff);
}

void Mesh::Render(Texture& texture)
{
	auto pSRV = texture.GetSRV();
	if (pSRV == nullptr) return;
	// Dest 전체 이미지 
	// Src 내가 뿌리고 싶은 이미지의 부분
	// 해당 함수 호출전에 텍스처에게 뿌리고싶은 이미지의 부분을 세팅 
	
	/*SetTexCoord({0,0,500,500});
	SetUV({0,0,500,500},500,500);*/
	SetTexCoord(texture.GetDestRect());
	SetUV(texture.GetSrcRect(), texture.GetWidth(), texture.GetHeight());
	const UINT stride = sizeof(PCTVertex);
	const UINT offset = 0u;

	pImmediateContext->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset);
	pImmediateContext->PSSetShaderResources(0u, 1u, &pSRV);
	pImmediateContext->UpdateSubresource(pVertexBuffer, 0u, nullptr, vertices, 0u, 0u);
	pImmediateContext->UpdateSubresource(pConstBuffer, 0u, 0u, &cb, 0u, 0u);
	pImmediateContext->DrawIndexed(6u, 0u, 0u);
}

void Mesh::SetTexCoord(D2D1_RECT_F rt)
{
	D2D1_RECT_F dest = {
		(rt.left) / Graphics::GetScreenWidth() * 2.0f - 1.0f,
		-((rt.top) / Graphics::GetScreenHeight() * 2.0f - 1.0f),
		(rt.right) / Graphics::GetScreenWidth() * 2.0f - 1.0f,
		-((rt.bottom) / Graphics::GetScreenHeight() * 2.0f - 1.0f)
	};
	
	vertices[0].x = dest.left;	vertices[0].y = dest.top;
	vertices[1].x = dest.right; vertices[1].y = dest.top;
	vertices[2].x = dest.left;	vertices[2].y = dest.bottom;
	vertices[3].x = dest.right; vertices[3].y = dest.bottom;
};

void Mesh::SetUV(D2D1_RECT_F rt, UINT w, UINT h)
{
	rt = {
		rt.left / w,
		rt.top / h,
		rt.right / w,
		rt.bottom / h
	};
	
	vertices[0].u = rt.left; vertices[0].v = rt.top;
	vertices[1].u = rt.right; vertices[1].v = rt.top;
	vertices[2].u = rt.left; vertices[2].v = rt.bottom;
	vertices[3].u = rt.right; vertices[3].v = rt.bottom;
}