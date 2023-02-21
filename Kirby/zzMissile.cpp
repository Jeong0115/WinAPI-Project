#include "zzMissile.h"
#include "zzTime.h"

namespace zz
{
	Missile::Missile()
		: mDir(1.f)
	{
	}

	Missile::~Missile()
	{
	}

	void Missile::Initialize()
	{
	}

	void Missile::Update()
	{
		Vector2 pos = GetPos();

		pos.y += 500.f * Time::DeltaTime() * (float)mDir;

		SetPos(pos);
	}

	void Missile::Render(HDC hdc)
	{
		Vector2 vPos = GetPos();
		Vector2 vScale = GetScale();

		HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Ellipse(hdc, vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2.f,
			vPos.x + vScale.x / 2.f, vPos.y + vScale.y / 2.f);

		SelectObject(hdc, oldPen);
		DeleteObject(pen);
	}
}
