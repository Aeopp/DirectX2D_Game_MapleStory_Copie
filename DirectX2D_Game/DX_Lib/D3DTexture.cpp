#include "D3DTexture.h"
#include <tchar.h>
#include "Graphics.h"
#pragma comment (lib, "DirectXTex.lib")
using namespace DirectX;

namespace FramebufferShaders
{
	#include "FramebufferVS.shh"
	#include "FramebufferPS.shh"
};

Texture::~Texture()
{
	if (pTexture) pTexture->Release();
}

ScratchImage Texture::LoadTextureFromFile(std::wstring filePath)
{
	HRESULT hr;
	std::wstring path = filePath;
	ScratchImage texture;
	WCHAR extension[_MAX_EXT];
	_wsplitpath_s(filePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, extension, _MAX_EXT);

	if (_wcsicmp(extension, L".dds") == 0)
	{
		hr = LoadFromDDSFile( filePath.c_str(), 
			DirectX::DDS_FLAGS_NONE, 
			nullptr, texture);
	}
	else if (_wcsicmp(extension, L".tga") == 0)
	{
		hr = LoadFromTGAFile( filePath.c_str(), 
			nullptr, texture);
	}
	else
	{
		hr = LoadFromWICFile(filePath.c_str(), 
			WIC_FLAGS_NONE, 
			nullptr, texture);
	}

	return texture;
}

bool Texture::LoadTexture(ID3D11Device* pDevice, std::wstring filePath)
{
	ScratchImage texture = LoadTextureFromFile(filePath);

   TexMetadata metadata = texture.GetMetadata();
	imageWidth = metadata.width;
	imageHeight = metadata.height;

	// Camera 좌표 기준 캐릭터 렉트 
	rtDest = { 0,0,(float)Graphics::GetScreenWidth(),(float)Graphics::GetScreenHeight() };
	// 애니메이션 텍스처 렉트
	rtSrc = { 0, 0, (float)imageWidth, (float)imageHeight };

	HRESULT hr;
	if (FAILED( hr = CreateShaderResourceView(
		pDevice,
		texture.GetImages(),
		1,
		metadata,
		&pTexture)))
	{
		MessageBox(nullptr, L"Failed To Load Texture", L"ERROR", MB_OK);
		PostQuitMessage(0);
	};
	return true;
}

bool Texture::LoadScript(std::wstring filePath)
{
	FILE* f;
	_wfopen_s(&f, filePath.c_str(), L"rt");
	if (f == NULL) return false;

	TCHAR pBuffer[256] = { 0 };
	TCHAR pTemp[256] = { 0 };
	int nFrame;

	_fgetts(pBuffer, _countof(pBuffer), f);
	_stscanf_s(pBuffer, _T("%s %d %s"), pTemp, _countof(pTemp), &nFrame);

	for (int iCnt = 0; iCnt < nFrame; iCnt++)
	{
		int iNumFrame = 0;
		_fgetts(pBuffer, _countof(pBuffer), f);
		_stscanf_s(pBuffer, _T("%s %d"), pTemp, _countof(pTemp), &iNumFrame);
		RECT rt;
		for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
		{
			_fgetts(pBuffer, _countof(pBuffer), f);
			_stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, _countof(pTemp),
				&rt.left, &rt.top, &rt.right, &rt.bottom);
			frameList.push_back(rt);
		}
	}
	fclose(f);
	return true;
}

ID3D11ShaderResourceView* Texture::GetSRV()
{
	return pTexture;
}

void Texture::SetDestRect(D2D1_RECT_F rt)
{
	rtDest = rt;
}

void Texture::SetSrcRect(D2D1_RECT_F rt)
{
	rtSrc = rt;
}

void Texture::SetFrame(UINT index)
{
	assert( index >= 0 && index < frameList.size());

	RECT tmp = frameList[index];
	rtSrc = { (float)tmp.left, (float)tmp.top, (float)tmp.right, (float)tmp.bottom };
}

D2D1_RECT_F Texture::GetDestRect()
{
	return rtDest;
}

D2D1_RECT_F Texture::GetSrcRect()
{
	return rtSrc;
}

UINT Texture::GetSingleWidth(UINT index)
{
	if (frameList.size() == 0u) return imageWidth;
	else return frameList[index].right - frameList[index].left;
}

UINT Texture::GetSingleHeight(UINT index)
{
	if (frameList.size() == 0u) return imageHeight;
	else return frameList[index].bottom - frameList[index].top;
}