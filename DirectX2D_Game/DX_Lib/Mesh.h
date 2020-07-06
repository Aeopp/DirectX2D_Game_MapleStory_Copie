#pragma once
#include <d3d11.h>
#include <d2d1.h>

class Texture;

class Mesh
{
public:
	struct PCTVertex
	{
		float x, y, z;
		float r, g, b, a;
		float u, v;
	};
	struct ConstBuffer
	{
		float r, g, b, a;
		float x, y, z, delta;
	};
private:
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pImmediateContext;

	ID3D11PixelShader* pPixelShader;
	ID3D11VertexShader* pVertexShader;
	ID3D11InputLayout* pInputLayout;
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer* pIndexBuffer;
	ID3D11Buffer* pConstBuffer;

	ID3D11SamplerState* pSamplerState;
	ID3D11BlendState* pBlendState;
	ID3D11RasterizerState* pRasterizerState;

	PCTVertex vertices[4];
	ConstBuffer cb;
public:
	Mesh() = default;
	~Mesh();

	Mesh(const Mesh&) = delete;
	Mesh& operator =(const Mesh&) = delete;

private:
	// world Rect -> NDC  -> VBUf Apply
	void SetTexCoord(D2D1_RECT_F rt);
	// Camera Animation
	void SetUV(D2D1_RECT_F rt, UINT w, UINT h);

public:
	void Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);
	void Render(Texture& texture);
};