#include "zzIceKirby.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	IceKirby::IceKirby(Kirby* owner)
		: mTex(nullptr)
		, mColli(nullptr)
		, mAni(nullptr)
		, mOwner(owner)

	{
	}

	IceKirby::~IceKirby()
	{
	}

	void IceKirby::Initialize()
	{
		mColli = AddComponent<Collider>();
		mAni = AddComponent<Animator>();

		Texture* IceKirbyWalkRight = ResourceMgr::Load<Texture>(L"IceKirbyWalkRight", L"..\\Resources\\IceKirby_Walk_Right.bmp");
		Texture* IceKirbyWalkLeft = ResourceMgr::Load<Texture>(L"IceKirbyWalkLeft", L"..\\Resources\\IceKirby_Walk_Left.bmp");
		
		Texture* IceKirby_Right = ResourceMgr::Load<Texture>(L"IceKirby_Right", L"..\\Resources\\IceKirby_Right.bmp");
		Texture* IceKirby_Left = ResourceMgr::Load<Texture>(L"IceKirby_Left", L"..\\Resources\\IceKirby_Left.bmp");

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Stay", Vector2(7.f, 4.f), Vector2(21.f, 25.f), Vector2(21.f, 0.f), 0.8f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Stay", Vector2(569.f, 4.f), Vector2(21.f, 25.f), Vector2(-21.f, 0.f), 0.8f, 2);

		mAni->CreateAnimation(IceKirbyWalkRight, L"IceKirbyWalkRight", Vector2(0.f, 0.f), Vector2(26.f, 27.f), Vector2(26.f, 0.f), 0.1f, 10);
		mAni->CreateAnimation(IceKirbyWalkLeft, L"IceKirbyWalkLeft", Vector2(234.f, 0.f), Vector2(26.f, 27.f), Vector2(-26.f, 0.f), 0.1f, 10);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_X", Vector2(181.f, 573.f), Vector2(22.f, 27.f), Vector2(22.f, 0.f), 0.1f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_X", Vector2(394.f, 573.f), Vector2(22.f, 27.f), Vector2(-22.f, 0.f), 0.1f, 2);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Down", Vector2(7.f, 41.f), Vector2(25.f, 19.f), Vector2(25.f, 0.f), 0.8f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Down", Vector2(565.f, 41.f), Vector2(25.f, 19.f), Vector2(-25.f, 0.f), 0.8f, 2);

		SetPos(mOwner->GetPos());
		SetScale(mOwner->GetScale());

		GameObject::Initialize();

	}

	void IceKirby::Update()
	{
		Vector2 vPos = GetPos();
		int dir = mOwner->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
		}
		else
		{
			mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
		}


		if (KEY(X, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_X", true);
		}


		else if (KEY(LEFT, PRESSED))
		{
			vPos.x -= (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(L"IceKirbyWalkLeft", true);
			dir = -1;
		}

		else if (KEY(RIGHT, PRESSED))
		{
			vPos.x += (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(L"IceKirbyWalkRight", true);
			dir = 1;
		}

		else if (KEY(DOWN, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Down", true);
			SetScale(Vector2(24.f, 15.f));
		}

		else if (KEY(DOWN, UP))
		{
			SetScale(mOwner->GetScale());
		}

		SetPos(vPos);
		mOwner->SetPos(vPos);
		mOwner->SetDir(dir);

		GameObject::Update();

	}

	void IceKirby::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}