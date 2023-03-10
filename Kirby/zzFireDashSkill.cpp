#include "zzFireDashSkill.h"

#include "zzTexture.h"
#include "zzTime.h"
#include "zzKey.h"
#include "zzKirby.h"

#include "zzPlayer.h"
namespace zz
{
	FireDashSkill::FireDashSkill(Vector2 pos, int dir)
		: mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(-10.f, 10.f))
		, mPassedTime(0.f)
		, mOwner(nullptr)
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* FireKirby_Right = ResourceMgr::Load<Texture>(L"FireKirby_Right", L"..\\Resources\\FireKirby_Right.bmp");
		Texture* FireKirby_Left = ResourceMgr::Load<Texture>(L"FireKirby_Left", L"..\\Resources\\FireKirby_Left.bmp");

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_DashSkill", Vector2(0.f, 836.f), Vector2(59.f, 38.f), Vector2(59.f, 0.f), 0.03f, 9);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_DashSkill", Vector2(635.f, 836.f), Vector2(59.f, 38.f), Vector2(-59.f, 0.f), 0.043f, 9);

		SetScale(Vector2(59.f, 38.f));

		pos.y += mIntervalPos.y;
		if (dir == 1)
		{
			pos.x += mIntervalPos.x;
			mAni->PlayAnimation(L"FireKirby_Right_DashSkill", true);
		}
		else
		{
			pos.x -= mIntervalPos.x;
			mAni->PlayAnimation(L"FireKirby_Left_DashSkill", true);
		}
		SetPos(pos);
		SetDir(dir);
	}

	FireDashSkill::~FireDashSkill()
	{
	}

	void FireDashSkill::Initialize()
	{
	}

	void FireDashSkill::Update()
	{
		SetPos(Vector2(mOwner->GetPos().x + mIntervalPos.x * GetDir(), mOwner->GetPos().y + mIntervalPos.y));
		mPassedTime += (float)Time::DeltaTime();

		if (mPassedTime > 1.2f && !IsDead())
		{
			DeleteObject(this, eLayerType::SKILL);
		}


		GameObject::Update();
	}

	void FireDashSkill::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}
}
