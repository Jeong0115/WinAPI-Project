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
		int Initialize(HWND hWnd, POINT resolution);
		void Run();
		inline HWND GetHwnd() { return mHwnd; }

	private:
		void Update();
		void Render();
	
	private:
		HWND	mHwnd;
		HDC		mHdc;
		POINT	mResolution;

		HBITMAP mHBit;
		HDC		mHBitDc;
	};

}

