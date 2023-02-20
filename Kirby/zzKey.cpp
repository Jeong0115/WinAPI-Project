#include "zzKey.h"
#include "zzApplication.h"

extern zz::Application application;

namespace zz
{
	std::vector<Key::KeyInfo> Key::mVecKeyInfo;

	int ASCII[(UINT)eKeyCode::LAST] =
	{
		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		'Z', 'X', 'Q', VK_RETURN, VK_RETURN
	};

	void Key::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::LAST; i++)
		{
			mVecKeyInfo.push_back(KeyInfo{ (eKeyCode)i, eKeyState::NONE, false });
		}
	}

	void Key::Update()
	{
		HWND hWnd = application.GetHwnd();
		HWND nowHwnd = GetFocus();

		if (hWnd == nowHwnd)
		{
			for (UINT i = 0; i < (UINT)eKeyCode::LAST; i++)
			{
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					if (mVecKeyInfo[i].bPressed)
						mVecKeyInfo[i].state = eKeyState::PRESSED;
					else
						mVecKeyInfo[i].state = eKeyState::DOWN;

					mVecKeyInfo[i].bPressed = true;
				}
				else
				{
					if (mVecKeyInfo[i].bPressed)
						mVecKeyInfo[i].state = eKeyState::UP;
					else
						mVecKeyInfo[i].state = eKeyState::NONE;

					mVecKeyInfo[i].bPressed = false;
				}
			}
		}
		else
		{
			for (UINT i = 0; i < (UINT)eKeyCode::LAST; i++)
			{
				mVecKeyInfo[i].bPressed = false;

				if (mVecKeyInfo[i].state == eKeyState::DOWN || mVecKeyInfo[i].state == eKeyState::PRESSED)
				{
					mVecKeyInfo[i].state = eKeyState::UP;
				}
				else if (mVecKeyInfo[i].state == eKeyState::UP)
				{
					mVecKeyInfo[i].state = eKeyState::NONE;
				}
			}
		}
	}
}