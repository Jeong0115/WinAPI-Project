#pragma once

#include "zzResource.h"

namespace zz
{
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

	public:
		virtual HRESULT Load(const std::wstring& path) override;

		UINT  GetWidth()	{ return mWidth; }
		UINT  GetHeight()	{ return mHeight; }
		HDC	  GetHdc()		{ return mHdc; }

	private:
		HBITMAP mBitMap;
		HDC		mHdc;
		UINT	mWidth;
		UINT	mHeight;

	};
}

