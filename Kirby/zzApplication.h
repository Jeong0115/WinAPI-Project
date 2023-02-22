#pragma once

#include "zzEngine.h"

namespace zz
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

	public:
		static int Initialize(HWND hWnd, POINT resolution);
		static void  Run();
		inline static HWND GetHwnd() { return mHwnd; }
		inline static HDC  GetHdc() { return mHdc; }
		inline static HDC  GetBitMapHdc() { return mBitMapHdc; }
		inline static POINT GetResolution() { return mResolution; }

	private:
		static void Update();
		static void Render();
	
	private:
		static HWND		mHwnd;
		static HDC		mHdc;
		static POINT	mResolution;

		static HBITMAP  mBitMap;
		static HDC		mBitMapHdc;
	};

}

