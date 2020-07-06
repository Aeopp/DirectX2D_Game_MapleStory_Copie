#pragma once
#include "Graphics.h"
#include <DirectXTex.h>
#include <DirectXTex.inl>

#include <vector>
#include <string>

class Texture
{
private:
	ID3D11ShaderResourceView* pTexture;
	std::vector<RECT> frameList;
	UINT currentFrame = 0u;
	
	D2D1_RECT_F rtDest;
	D2D1_RECT_F rtSrc;

	UINT imageWidth = 0u;
	UINT imageHeight = 0u;
public:
	Texture() = default;
	~Texture();

	Texture(const Texture&) = delete;
	Texture& operator =(const Texture&) = delete;

private:
	static DirectX::ScratchImage LoadTextureFromFile(std::wstring fileName);
public:
	                                               // FUll
	bool LoadTexture(ID3D11Device* pDevice, std::wstring filePath);
	bool LoadScript(std::wstring filePath);

	ID3D11ShaderResourceView* GetSRV();
	// 전체
	void SetDestRect(D2D1_RECT_F rt);
	// 부분
	void SetSrcRect(D2D1_RECT_F rt);
	void SetFrame(UINT index);

	D2D1_RECT_F GetDestRect();
	D2D1_RECT_F GetSrcRect();

	UINT GetMaxFrame() { return frameList.size(); }
	UINT GetWidth() { return imageWidth; }
	UINT GetHeight() { return imageHeight; }
	UINT GetSingleWidth(UINT index = 0);
	UINT GetSingleHeight(UINT index = 0);
};