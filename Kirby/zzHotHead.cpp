#include "zzHotHead.h"
#include "zzTime.h"
#include "zzDefaultSkill.h"
#include "zzPlayer.h"

namespace zz
{
	HotHead::HotHead()
		: mCenterPos(Vector2(0.f, 0.f))
		, mSpeed(40.f)
		, mMaxDistance(70.f)
		, mColli(nullptr)
		, mAni(nullptr)
		, mState(eHothead::MOVE)
	{
		SetType(eAbillityType::FIRE);
	}
	HotHead::~HotHead()
	{
	}
	void HotHead::Initialize()
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* Enemies_Right = ResourceMgr::Load<Texture>(L"Enemies_Right", L"..\\Resources\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceMgr::Load<Texture>(L"Enemies_Left", L"..\\Resources\\Enemies_Left.bmp");

		mAni->CreateAnimation(Enemies_Right, L"Enemies_Right_Walk", Vector2(0.f, 3260.f), Vector2(22.f, 21.f), Vector2(22.f, 0.f), 0.18f, 8);
		mAni->CreateAnimation(Enemies_Left, L"Enemies_Left_Walk", Vector2(460.f, 3260.f), Vector2(22.f, 21.f), Vector2(-22.f, 0.f), 0.18f, 8);


		mAni->CreateAnimation(Enemies_Right, L"Enemies_Right_Inhale", Vector2(0.f, 3350.f), Vector2(23.f, 21.f), Vector2(23.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(Enemies_Left, L"Enemies_Left_Inhale", Vector2(459.f, 3350.f), Vector2(23.f, 21.f), Vector2(-23.f, 0.f), 1.f, 1);


		SetPos(Vector2(500.f, 145.f));
		SetScale(Vector2(22.f, 21.f));

		SetCenterPos(GetPos());

		mAni->PlayAnimation(L"Enemies_Right_Walk", true);

		GameObject::Initialize();
	}
	void HotHead::Update()
	{
		switch (mState)
		{
		case eHothead::MOVE:
			move();
			break;

		case eHothead::ATTACK:
			attack();
			break;

		case eHothead::INHALE:
			inhale();
			break;

		}

		GameObject::Update();
	}
	void HotHead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void HotHead::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE)
		{
			SetState(eState::INHALE);
			mState = eHothead::INHALE;
			mDiffPos = dynamic_cast<DefaultSkill*>(other)->GetOwner()->GetPos() - GetPos();
		
			mAni->PlayAnimation(L"Enemies_Right_Inhale", true);
		}
	}
	void HotHead::OnCollision(GameObject* other)
	{
	}
	void HotHead::OnCollisionExit(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE)
		{
			SetState(eState::ACTIVE);
			mState = eHothead::MOVE;
			int dir = GetDir();
			if (dir == 1)
			{
				mAni->PlayAnimation(L"Enemies_Right_Walk", true);
			}
			else
			{
				mAni->PlayAnimation(L"Enemies_Left_Walk", true);
			}
		}
	}
	void HotHead::move()
	{
		Vector2 curPos = GetPos();
		int dir = GetDir();

		curPos.x += (float)Time::DeltaTime() * mSpeed * dir;

		float dist = abs(mCenterPos.x - curPos.x) - mMaxDistance;

		if (0.f < dist)
		{
			dir *= -1;
			curPos.x += dist * dir;
			if (dir == 1)
			{
				mAni->PlayAnimation(L"Enemies_Right_Walk", true);
			}
			else
			{
				mAni->PlayAnimation(L"Enemies_Left_Walk", true);
			}
		}

		SetPos(curPos);
		SetDir(dir);
	}
	void HotHead::attack()
	{
	}
	void HotHead::inhale()
	{
		SetPos(GetPos() + mDiffPos * 2.f * (float)Time::DeltaTime());
	}
}