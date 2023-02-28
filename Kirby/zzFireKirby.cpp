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

		Texture* FireKirbyStayRight = ResourceMgr::Load<Texture>(L"FireKirbyStayRight", L"..\\Resources\\FireKirby_Staty_Right.bmp");
		Texture* FireKirbyStayLeft = ResourceMgr::Load<Texture>(L"FireKirbyStayLeft", L"..\\Resources\\FireKirby_Staty_Left.bmp");
		Texture* FireKirbyWalkRight = ResourceMgr::Load<Texture>(L"FireKirbyWalkRight", L"..\\Resources\\FireKirby_Walk_Right.bmp");
		Texture* FireKirbyWalkLeft = ResourceMgr::Load<Texture>(L"FireKirbyWalkLeft", L"..\\Resources\\FireKirby_Walk_Left.bmp");

		Texture* FireKirby_Right = ResourceMgr::Load<Texture>(L"FireKirby_Right", L"..\\Resources\\FireKirby_Right.bmp");
		Texture* FireKirby_Left = ResourceMgr::Load<Texture>(L"FireKirby_Left", L"..\\Resources\\FireKirby_Left.bmp");

		mAni->CreateAnimation(FireKirbyStayRight, L"FireKirbyStayRight", Vector2(0.f, 0.f), Vector2(26.375f, 33.f), Vector2(26.375f, 0.f), 0.2f, 8);
		mAni->CreateAnimation(FireKirbyStayLeft, L"FireKirbyStayLeft", Vector2(184.625f, 0.f), Vector2(26.375f, 33.f), Vector2(-26.375f, 0.f), 0.2f, 8);
		mAni->CreateAnimation(FireKirbyWalkRight, L"FireKirbyWalkRight", Vector2(0.f, 0.f), Vector2(27.3f, 37.f), Vector2(27.35f, 0.f), 0.05f, 20);
		mAni->CreateAnimation(FireKirbyWalkLeft, L"FireKirbyWalkLeft", Vector2(518.7f, 0.f), Vector2(27.3f, 37.f), Vector2(-27.35f, 0.f), 0.05f, 20);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_X", Vector2(187.f, 1109.f), Vector2(31.f, 29.f), Vector2(31.f, 0.f), 0.05f, 4);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_X", Vector2(476.f, 1109.f), Vector2(31.f, 29.f), Vector2(-31.f, 0.f), 0.05f, 4);

		SetPos(mOwner->GetPos());
		SetScale(mOwner->GetScale());

		GameObject::Initialize();
	}

	void FireKirby::Update()
	{
		Vector2 vPos = GetPos();

		if (mOwner->mDir == 1)
		{
			mAni->PlayAnimation(L"FireKirbyStayRight", true);
		}
		else
		{
			mAni->PlayAnimation(L"FireKirbyStayLeft", true);
		}

		if (KEY(LEFT, PRESSED))
		{
			vPos.x -= (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(L"FireKirbyWalkLeft", true);
			mOwner->mDir = -1;
		}

		if (KEY(RIGHT, PRESSED))
		{
			vPos.x += (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(L"FireKirbyWalkRight", true);
			mOwner->mDir = 1;
		}

		if (mOwner->mDir == 1 && KEY(X, PRESSED))
		{
			mAni->PlayAnimation(L"FireKirby_Right_X", true);
		}
		else if (mOwner->mDir != 1 && KEY(X, PRESSED))
		{
			mAni->PlayAnimation(L"FireKirby_Left_X", true);
		}
		//if (KEY(RIGHT, UP))
		//{
		//	//mAni->StopAnimation(L"Kirby");
		//	mAni->PlayAnimation(mStayRightKeys[state], true);
		//}


		SetPos(vPos);
		mOwner->SetPos(vPos);
		
		GameObject::Update();

	}

	void FireKirby::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}