#include "zzMonster.h"
#include "zzTime.h"

namespace zz
{
	Monster::Monster()
		: mSpeed(100.f)
		, mCenterPos{ Vector2(0.f,0.f) }
		, mMaxDistance(80.f)
		, mDir(1)
	{
	}

	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		GameObject::Initialize();

		monsterTexture = ResourceMgr::Load<Texture>(L"monsetr", L"..\\Resources\\Monster_Right.bmp");

		SetPos(Vector2( 500.f, 95.f ));
		SetCenterPos(Vector2(GetPos().x +50 , GetPos().y));
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
			if (mDir > 0)
			{
				monsterTexture = ResourceMgr::Load<Texture>(L"Monster_Right", L"..\\Resources\\Monster_Right.bmp");
			}
			else
			{
				monsterTexture = ResourceMgr::Load<Texture>(L"Monster_Left", L"..\\Resources\\Monster_Left.bmp");

			}
		}

		SetPos(curPos);
	}

	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Vector2 vPos = GetPos();

		TransparentBlt(hdc, vPos.x, vPos.y, monsterTexture->GetWidth(),
			monsterTexture->GetHeight(), monsterTexture->GetHdc(), 0, 0,
			monsterTexture->GetWidth(), monsterTexture->GetHeight(), RGB(0, 255, 0));
	}
}
