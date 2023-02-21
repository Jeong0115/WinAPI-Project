#include "zzMonster.h"
#include "zzTime.h"

namespace zz
{
	Monster::Monster()
		: mSpeed(200.f)
		, mCenterPos{ Vector2(0.f,0.f) }
		, mMaxDistance(100.f)
		, mDir(1)
	{
	}

	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		GameObject::Initialize();

		//SetPos(Vector2( 500.f, 500.f ));
		//SetCenterPos(Vector2(GetPos().x +50 , GetPos().y));
	}

	void Monster::Update()
	{
		GameObject::Update();

		Vector2 curPos = GetPos();

		curPos.x += Time::DeltaTime() * mSpeed * mDir;

		float dist = abs(mCenterPos.x - curPos.x) - mMaxDistance;

		if (0.f < dist)
		{
			mDir *= -1;
			curPos.x += dist * mDir;
		}

		SetPos(curPos);
	}

	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Vector2 vPos = GetPos();

		HPEN pen = CreatePen(PS_SOLID, 5, RGB(200, 100, 150));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc, vPos.x, vPos.y, vPos.x + 100, vPos.y + 100);

		SelectObject(hdc, oldPen);
		DeleteObject(pen);
	}
}
