#include "zzApplication.h"

#include "zzSceneMgr.h"
#include "zzCollisionMgr.h"
#include "zzEventMgr.h"
#include "zzTime.h"
#include "zzKey.h"


namespace zz
{	
	HWND		Application::mHwnd			= 0;
	HDC			Application::mHdc			= 0;
	POINT		Application::mResolution	= {};
	HDC			Application::mBitMapHdc		= 0;
	HBITMAP		Application::mBitMap		= 0;

	HBRUSH		Application::mHollowBrush	= (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HPEN		Application::mGreenPen		= (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN		Application::mRedPen		= (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN		Application::mPen			= mGreenPen;

	Application::Application()
	{

	}

	Application::~Application()
	{
		ReleaseDC(mHwnd, mHdc);

		DeleteDC(mBitMapHdc);
		DeleteObject(mBitMap);

		DeleteObject(mGreenPen);
		DeleteObject(mRedPen);
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
		Camera::Initialize();

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
		Camera::Update();

		SceneMgr::Update();
		CollisionMgr::Update();
		//EventMgr::Update();
		
	}

	void Application::Render()
	{
		Rectangle(mBitMapHdc, -1, -1, mResolution.x + 1, mResolution.y + 1);

		SceneMgr::Render(mBitMapHdc);

		RECT rect;

		BitBlt(mHdc, 0, 0, mResolution.x, mResolution.y, mBitMapHdc, 0, 0, SRCCOPY);

		SetMapMode(mHdc, MM_ISOTROPIC);
		SetWindowExtEx(mHdc, mResolution.x, mResolution.y, NULL);
		GetClientRect(mHwnd, &rect);
		SetViewportExtEx(mHdc, rect.right, rect.bottom, NULL);

		EventMgr::Update();
	}
}