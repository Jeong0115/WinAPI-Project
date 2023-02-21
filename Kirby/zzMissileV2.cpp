#include "zzMissileV2.h"
#include "zzTime.h"

namespace zz
{
	MissileV2::MissileV2()
		: mDir(1.f)
	{
	}

	MissileV2::~MissileV2()
	{
	}

	void MissileV2::Initialize()
	{
	}

	void MissileV2::Update()
	{
		Vector2 pos = GetPos();

		pos.y += 500.f * Time::DeltaTime() * (float)mDir;

		SetPos(pos);
	}

	void MissileV2::Render(HDC hdc)
	{
		Vector2 vPos = GetPos();
		Vector2 vScale = GetScale();

		HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Ellipse(hdc, vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2.f,
			vPos.x + vScale.x / 2.f, vPos.y + vScale.y / 2.f);

		SelectObject(hdc, oldPen);
		DeleteObject(pen);
	}
}