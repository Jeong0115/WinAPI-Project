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

		Texture* IceKirbyStayRight = ResourceMgr::Load<Texture>(L"IceKirbyStayRight", L"..\\Resources\\IceKirby_Staty_Right.bmp");
		Texture* IceKirbyStayLeft = ResourceMgr::Load<Texture>(L"IceKirbyStayLeft", L"..\\Resources\\IceKirby_Staty_Left.bmp");
		Texture* IceKirbyWalkRight = ResourceMgr::Load<Texture>(L"IceKirbyWalkRight", L"..\\Resources\\IceKirby_Walk_Right.bmp");
		Texture* IceKirbyWalkLeft = ResourceMgr::Load<Texture>(L"IceKirbyWalkLeft", L"..\\Resources\\IceKirby_Walk_Left.bmp");
		
		Texture* IceKirby_Right = ResourceMgr::Load<Texture>(L"IceKirby_Right", L"..\\Resources\\IceKirby_Right.bmp");
		Texture* IceKirby_Left = ResourceMgr::Load<Texture>(L"IceKirby_Left", L"..\\Resources\\IceKirby_Left.bmp");

		mAni->CreateAnimation(IceKirbyStayRight, L"IceKirbyStayRight", Vector2(0.f, 0.f), Vector2(26.f, 29.f), Vector2(26.f, 0.f), 0.8f, 2);
		mAni->CreateAnimation(IceKirbyStayLeft, L"IceKirbyStayLeft", Vector2(26.f, 0.f), Vector2(26.f, 29.f), Vector2(-26.f, 0.f), 0.8f, 2);
		mAni->CreateAnimation(IceKirbyWalkRight, L"IceKirbyWalkRight", Vector2(0.f, 0.f), Vector2(26.f, 27.f), Vector2(26.f, 0.f), 0.1f, 10);
		mAni->CreateAnimation(IceKirbyWalkLeft, L"IceKirbyWalkLeft", Vector2(234.f, 0.f), Vector2(26.f, 27.f), Vector2(-26.f, 0.f), 0.1f, 10);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_X", Vector2(181.f, 573.f), Vector2(22.f, 27.f), Vector2(22.f, 0.f), 0.1f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_X", Vector2(394.f, 573.f), Vector2(22.f, 27.f), Vector2(-22.f, 0.f), 0.1f, 2);

		SetPos(mOwner->GetPos());
		SetScale(mOwner->GetScale());

		GameObject::Initialize();

	}

	void IceKirby::Update()
	{
		Vector2 vPos = GetPos();

		if (mOwner->mDir == 1)
		{
			mAni->PlayAnimation(L"IceKirbyStayRight", true);
		}
		else
		{
			mAni->PlayAnimation(L"IceKirbyStayLeft", true);
		}

		if (KEY(LEFT, PRESSED))
		{
			vPos.x -= (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(L"IceKirbyWalkLeft", true);
			mOwner->mDir = -1;
		}

		if (KEY(RIGHT, PRESSED))
		{
			vPos.x += (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(L"IceKirbyWalkRight", true);
			mOwner->mDir = 1;
		}

		if (mOwner->mDir == 1 && KEY(X, PRESSED))
		{
			mAni->PlayAnimation(L"IceKirby_Right_X", true);
		}
		else if (mOwner->mDir != 1 && KEY(X, PRESSED))
		{
			mAni->PlayAnimation(L"IceKirby_Left_X", true);
		}


		SetPos(vPos);
		mOwner->SetPos(vPos);


		GameObject::Update();

	}

	void IceKirby::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}