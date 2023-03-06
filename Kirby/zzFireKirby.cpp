#include "zzFireKirby.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	FireKirby::FireKirby(Kirby* owner)
		: mTex(nullptr)
		, mColli(nullptr)
		, mAni(nullptr)
		, mOwner(owner)
	{
	}

	FireKirby::~FireKirby()
	{
	}

	void FireKirby::Initialize()
	{
		mColli = AddComponent<Collider>();
		mAni = AddComponent<Animator>();

		Texture* FireKirby_Right = ResourceMgr::Load<Texture>(L"FireKirby_Right", L"..\\Resources\\FireKirby_Right.bmp");
		Texture* FireKirby_Left = ResourceMgr::Load<Texture>(L"FireKirby_Left", L"..\\Resources\\FireKirby_Left.bmp");

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Stay", Vector2(8.f, 4.f), Vector2(23.f, 32.f), Vector2(23.f, 0.f), 0.08f, 8);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Stay", Vector2(663.f, 4.f), Vector2(23.f, 32.f), Vector2(-23.f, 0.f), 0.08f, 8);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Down", Vector2(230.f, 10.f), Vector2(27.f, 26.f), Vector2(27.f, 0.f), 0.08f, 8);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Down", Vector2(437.f, 10.f), Vector2(27.f, 26.f), Vector2(-27.f, 0.f), 0.08f, 8);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Walk", Vector2(7.f, 292.f), Vector2(25.f, 36.f), Vector2(25.f, 0.f), 0.05f, 20);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Walk", Vector2(662.f, 292.f), Vector2(25.f, 36.f), Vector2(-25.f, 0.f), 0.05f, 20);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_X", Vector2(187.f, 1109.f), Vector2(31.f, 29.f), Vector2(31.f, 0.f), 0.05f, 4);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_X", Vector2(476.f, 1109.f), Vector2(31.f, 29.f), Vector2(-31.f, 0.f), 0.05f, 4);

		SetPos(mOwner->GetPos());
		SetScale(mOwner->GetScale());

		GameObject::Initialize();
	}

	void FireKirby::Update()
	{
		Vector2 vPos = mOwner->GetPos();
		int dir = mOwner->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
		}
		else
		{
			mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
		}

		if (KEY(X, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_X", true);
		}

		else if (KEY(LEFT, PRESSED))
		{
			vPos.x -= (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(L"FireKirby_Left_Walk", true);
			dir = -1;
		}

		else if (KEY(RIGHT, PRESSED))
		{
			vPos.x += (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(L"FireKirby_Right_Walk", true);
			dir = 1;
		}

		else if (KEY(DOWN, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Down", true);
			SetScale(Vector2(24.f, 15.f));
		}

		else if (KEY(DOWN, UP))
		{
			SetScale(mOwner->GetScale());
		}
		
		

		//if (KEY(RIGHT, UP))
		//{
		//	//mAni->StopAnimation(L"Kirby");
		//	mAni->PlayAnimation(mStayRightKeys[state], true);
		//}


		SetPos(vPos);
		mOwner->SetPos(vPos);
		mOwner->SetDir(dir);

		GameObject::Update();

	}

	void FireKirby::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}