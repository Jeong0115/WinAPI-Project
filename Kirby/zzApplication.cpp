#include "zzApplication.h"
#include "zzSceneMgr.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	Application::Application()
		: mHwnd(0)
		, mHdc(0)
		, mResolution{}
		, mHBitDc(0)
		, mHBit(0)
	{}

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

		mHBit = CreateCompatibleBitmap(mHdc, mResolution.x, mResolution.y);
		mHBitDc = CreateCompatibleDC(mHdc);

		HBITMAP hOldBit = (HBITMAP)SelectObject(mHBitDc, mHBit);
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
		Rectangle(mHBitDc, -1, -1, mResolution.x, mResolution.y);

		SceneMgr::Render(mHBitDc);

		BitBlt(mHdc, 0, 0, mResolution.x, mResolution.y, mHBitDc, 0, 0, SRCCOPY);
	}
}