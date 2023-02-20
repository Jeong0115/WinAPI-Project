#include "zzKirby.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	Kirby::Kirby()
	{
	}

	Kirby::~Kirby()
	{
	}

	void Kirby::Initialize()
	{
		GameObject::Initialize();
	}

	void Kirby::Update()
	{
		GameObject::Update();

		if (Key::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			mPos.x -= 100.f * Time::DeltaTime();
		}

		if (Key::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			mPos.x += 100.f * Time::DeltaTime();
		}

		if (Key::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			mPos.y -= 100.f * Time::DeltaTime();
		}

		if (Key::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			mPos.y += 100.f * Time::DeltaTime();
		}

		if (Key::GetKeyState(eKeyCode::Z) == eKeyState::DOWN)
		{
			mPos.y -= 100.f;
		}
	}

	void Kirby::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		HPEN pen = CreatePen(PS_SOLID, 5, RGB(30, 100, 20));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc, mPos.x, mPos.y, mPos.x + 100, mPos.y + 100);

		SelectObject(hdc, oldPen);
		DeleteObject(pen);
	}
}