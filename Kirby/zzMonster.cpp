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
		
		mTr = AddComponent<Transform>();
		mColli = AddComponent<Collider>();

		monsterTexture = ResourceMgr::Load<Texture>(L"monsetr", L"..\\Resources\\Monster_Right.bmp");

		mTr->SetPos(Vector2( 500.f, 120.f ));
		mTr->SetScale(Vector2(62.f, 55.f));

		mColli->SetPos(mTr->GetPos());
		mColli->SetScale(mTr->GetScale());

		SetCenterPos(Vector2(mTr->GetPos().x +50 , mTr->GetPos().y));
	}

	void Monster::Update()
	{
		GameObject::Update();

		Vector2 curPos = mTr->GetPos();

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

		mTr->SetPos(curPos);
		mColli->SetPos(curPos);
	}

	void Monster::Render(HDC hdc)
	{
		Vector2 vPos = mTr->GetPos();
		Vector2 vScale = mTr->GetScale();

		TransparentBlt(hdc, vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2.f, monsterTexture->GetWidth(),
			monsterTexture->GetHeight(), monsterTexture->GetHdc(), 0, 0,
			monsterTexture->GetWidth(), monsterTexture->GetHeight(), RGB(0, 255, 0));

		GameObject::Render(hdc);
	}
}
