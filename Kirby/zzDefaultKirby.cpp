#include "zzDefaultKirby.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	DefaultKirby::DefaultKirby(Kirby* owner)
		: mOwner(owner)
		, mAni(nullptr)
		, mColli(nullptr)
	{
	}

	DefaultKirby::~DefaultKirby()
	{
	}

	void DefaultKirby::Initialize()
	{
		mColli = AddComponent<Collider>();
		mAni = AddComponent<Animator>();

		Texture* DefaultKirby_Right = ResourceMgr::Load<Texture>(L"DefaultKirby_Right", L"..\\Resources\\DefaultKirby_Right.bmp");
		Texture* DefaultKirby_Left = ResourceMgr::Load<Texture>(L"DefaultKirby_Left", L"..\\Resources\\DefaultKirby_Left.bmp");


		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Walk", Vector2(253.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.1f, 10);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Walk", Vector2(726.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.1f, 10);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Stay", Vector2(8.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Stay", Vector2(972.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);


		SetPos(mOwner->GetPos());
		SetScale(mOwner->GetScale());

		GameObject::Initialize();
	}

	void DefaultKirby::Update()
	{
		Vector2 vPos = GetPos();

		if (mOwner->mDir == 1)
		{
			mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
		}
		else
		{
			mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}

		if (KEY(LEFT, PRESSED))
		{
			vPos.x -= (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(L"DefaultKirby_Left_Walk", true);
			mOwner->mDir = -1;
		}
		if (KEY(LEFT, UP))
		{
			mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}


		if (KEY(RIGHT, PRESSED))
		{
			vPos.x += (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(L"DefaultKirby_Right_Walk", true);
			mOwner->mDir = 1;
		}
		if (KEY(RIGHT, UP))
		{
			mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
		}

		mOwner->SetPos(vPos);
		SetPos(vPos);

		GameObject::Update();

	}

	void DefaultKirby::Render(HDC hdc)
	{
		
		GameObject::Render(hdc);

	}
}