#include "Pixel.h"
#include "PathManager.h"

CPixel::CPixel()
{
	m_iWidth = 0;
	m_iHeight = 0;
	Collision_Tag = ECollision_Tag::Pixel;
}

CPixel::CPixel(const CPixel& rhs)
{
	m_iWidth  = rhs.m_iWidth;
	m_iHeight = rhs.m_iHeight;
	Collision_Tag = rhs.Collision_Tag;
}

bool CPixel::SetPixelInfo(const char* pFileName, const wstring& strPathKey)
{
	const char* pPath = GET_SINGLE(CPathManager)->FindPathMultiByte(std::string(strPathKey.begin(), strPathKey.end()));

	string strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName; 

	FILE* pFile = NULL;

	fopen_s(&pFile, strPath.c_str(),
		"rb");

	if (!pFile)
		return false;

	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;

	fread(&fh, sizeof(fh), 1, pFile);
	fread(&ih, sizeof(ih), 1, pFile);

	m_iWidth = ih.biWidth;
	m_iHeight = ih.biHeight;

	m_vecPixel.clear();
	m_vecPixel.resize(m_iWidth * m_iHeight);

	fread(&m_vecPixel[0], sizeof(PIXEL), m_vecPixel.size(), pFile);

	PPIXEL pPixelArr = new PIXEL[m_iWidth];

	for (int i = 0; i < m_iHeight / 2; ++i) {
		memcpy(
			pPixelArr,
			&m_vecPixel[i * m_iWidth],
			sizeof(PIXEL) * m_iWidth);

		memcpy(&m_vecPixel[i * m_iWidth],
			&m_vecPixel
			[(m_iHeight - i - 1) * m_iWidth], sizeof(PIXEL) * m_iWidth);

		memcpy(&m_vecPixel[(m_iHeight - i - 1) * m_iWidth], pPixelArr,
			sizeof(PIXEL) * m_iWidth);
	};

	delete[] pPixelArr;

	fclose(pFile);

	fopen_s(&pFile, "Temp.bmp", "wb");

	fwrite(&fh, sizeof(fh), 1, pFile);
	fwrite(&ih, sizeof(ih), 1, pFile);
	fwrite(&m_vecPixel[0], sizeof(PIXEL),
		m_vecPixel.size(), pFile);
	fclose(pFile);


	return true; 

	// 파일 제대로 읽는지??

	//fclose(pFile);

	//fopen_s(&pFile, "Test777.bmp", "wb");

	//if (!pFile)
	//	return false;

	//fwrite(&fh, sizeof(fh), 1, pFile);
	//fwrite(&ih, sizeof(ih), 1, pFile);
	//fwrite(&m_vecPixel[0], sizeof(PIXEL), 1, pFile);

	//fclose(pFile);

	return true;
}

bool CPixel::Init()
{
	return true;
};

void CPixel::Input(float fDeltaTime)
{
};

int CPixel::Update(float fDeltaTime)
{
	return 0;
}

int CPixel::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CPixel::Collision(float fDeltaTime)
{
}

void CPixel::Hit(CObj* const Target, float fDeltaTime)
{
}

void CPixel::Render(HDC hDC, float fDeltaTime)
{
}

CPixel* CPixel::Clone()
{
	return new CPixel{ *this };
}
