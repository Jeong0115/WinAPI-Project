#include "zzApplication.h"
#include "zzSceneMgr.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	HWND	Application::mHwnd = 0;
	HDC		Application::mHdc = 0;
	POINT	Application::mResolution = {};
	HDC		Application::mBitMapHdc = 0;
	HBITMAP	Application::mBitMap = 0;

	Application::~Application()
	{

	}

	int Application::Initialize(HWND hWnd, POINT resolution)
	{
		mHwnd = hWnd;
		mHdc = GetDC(mHwnd);
		mResolution = resolution;

		RECT rect = { 0, 0, mResolution.x, mResolution.y };
		
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true);
		SetWindowPos(mHwnd, nullptr, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0);

		mBitMap = CreateCompatibleBitmap(mHdc, mResolution.x, mResolution.y);
		mBitMapHdc = CreateCompatibleDC(mHdc);

		HBITMAP hOldBit = (HBITMAP)SelectObject(mBitMapHdc, mBitMap);
		DeleteObject(hOldBit);

		Time::Initialize();
		Key::Initialize();
		SceneMgr::Initialize();

		return S_OK;
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		Key::Update();
		SceneMgr::Update();
	}

	void Application::Render()
	{
		//Rectangle(mBitMapHdc, -1, -1, mResolution.x, mResolution.y);

		SceneMgr::Render(mBitMapHdc);

		BitBlt(mHdc, 0, 0, mResolution.x, mResolution.y, mBitMapHdc, 0, 0, SRCCOPY);
	}
}