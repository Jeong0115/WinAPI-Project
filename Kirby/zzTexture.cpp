#include "zzTexture.h"
#include "zzApplication.h"

namespace zz
{
	Texture::Texture()
		: mBitMap(0)
		, mHdc(0)
		, mWidth(0)
		, mHeight(0)
	{
	}

	Texture::~Texture()
	{

	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		mBitMap = (HBITMAP)LoadImageW(nullptr, path.c_str(), 
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitMap == nullptr)
		{
			return E_FAIL;
		}

		BITMAP bitInfo = {};
		GetObject(mBitMap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDc = Application::GetHdc();
		mHdc = CreateCompatibleDC(mainDc);

		HBITMAP oldBitMap = (HBITMAP)SelectObject(mHdc, mBitMap);
		DeleteObject(oldBitMap);

		return S_OK;
	}
}