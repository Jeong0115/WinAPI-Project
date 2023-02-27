#include "zzMonster.h"
#include "zzTime.h"

namespace zz
{
	Monster::Monster()
		: mSpeed(100.f)
		, mCenterPos{ Vector2(0.f,0.f) }
		, mMaxDistance(80.f)
		, mDir(1)
		, monsterTexture(nullptr)
		, mTr(nullptr)
		, mColli(nullptr)
		, mAni(nullptr)
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

		monsterTexture = ResourceMgr::Load<Texture>(L"Monster_Right", L"..\\Resources\\Monster_Right.bmp");

		//mAni->CreateAnimation(monsterTexture, L"monster", Vector2(0.f, 0.f), Vector2(72.75f, 65.f), Vector2(72.75f, 0.f), 0.2f, 4);

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

		curPos.x += (float)Time::DeltaTime() * mSpeed * mDir;

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
				//mAni->PlayAnimation(L"monster", true);

			}
		}

		mTr->SetPos(curPos);
		mColli->SetPos(curPos);
	}

	void Monster::Render(HDC hdc)
	{
		Vector2 vPos = mTr->GetPos();
		Vector2 vScale = mTr->GetScale();

		TransparentBlt(hdc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f), monsterTexture->GetWidth(),
			monsterTexture->GetHeight(), monsterTexture->GetHdc(), 0, 0,
			monsterTexture->GetWidth(), monsterTexture->GetHeight(), RGB(0, 255, 0));

		GameObject::Render(hdc);
	}
}
