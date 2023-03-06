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
		, mState(eIceKirby::IDLE)

	{
	}

	IceKirby::~IceKirby()
	{
	}

	void IceKirby::Initialize()
	{
		mColli = AddComponent<Collider>();
		mAni = AddComponent<Animator>();

		Texture* IceKirby_Right_Walk = ResourceMgr::Load<Texture>(L"IceKirbyWalkRight", L"..\\Resources\\IceKirby_Right_Walk.bmp");
		Texture* IceKirby_Left_Walk = ResourceMgr::Load<Texture>(L"IceKirbyWalkLeft", L"..\\Resources\\IceKirby_Left_Walk.bmp");
		
		Texture* IceKirby_Right = ResourceMgr::Load<Texture>(L"IceKirby_Right", L"..\\Resources\\IceKirby_Right.bmp");
		Texture* IceKirby_Left = ResourceMgr::Load<Texture>(L"IceKirby_Left", L"..\\Resources\\IceKirby_Left.bmp");

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Stay", Vector2(7.f, 4.f), Vector2(21.f, 25.f), Vector2(21.f, 0.f), 0.8f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Stay", Vector2(569.f, 4.f), Vector2(21.f, 25.f), Vector2(-21.f, 0.f), 0.8f, 2);

		mAni->CreateAnimation(IceKirby_Right_Walk, L"IceKirby_Right_Walk", Vector2(0.f, 0.f), Vector2(26.f, 27.f), Vector2(26.f, 0.f), 0.1f, 10);
		mAni->CreateAnimation(IceKirby_Left_Walk, L"IceKirby_Left_Walk", Vector2(234.f, 0.f), Vector2(26.f, 27.f), Vector2(-26.f, 0.f), 0.1f, 10);

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
		int dir = mOwner->GetDir();

		switch (mState)
		{
		case IceKirby::eIceKirby::IDLE:
			idle(dir);
			break;

		case IceKirby::eIceKirby::MOVE:
			move(dir);
			break;

		case IceKirby::eIceKirby::SKILL:
			skill(dir);
			break;

		case IceKirby::eIceKirby::DOWN:
			down(dir);
			break;

		default:
			break;
		}

		GameObject::Update();
	}

	void IceKirby::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void IceKirby::Enter()
	{
	}

	void IceKirby::Exit()
	{
	}

	void IceKirby::idle(int dir)
	{
		if (KEY(LEFT, DOWN) || KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED) || KEY(LEFT, PRESSED))
		{
			mState = eIceKirby::MOVE;
			if (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED))
			{
				mAni->PlayAnimation(L"IceKirby_Left_Walk", true);
				dir = -1;
			}
			else if (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED))
			{
				mAni->PlayAnimation(L"IceKirby_Right_Walk", true);
				dir = 1;
			}
		}

		if (KEY(X, DOWN))
		{
			mState = eIceKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_X", true);
		}


		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Down", true);
			SetScale(Vector2(24.f, 15.f));

			mState = eIceKirby::DOWN;
		}

	}

	void IceKirby::move(int dir)
	{
		Vector2 vPos = mOwner->GetPos();
		int prevDir = mOwner->GetDir();

		if (KEY(LEFT, PRESSED))
		{
			vPos.x -= (float)(100.f * Time::DeltaTime());
			dir = -1;
		}

		if (KEY(RIGHT, PRESSED))
		{
			vPos.x += (float)(100.f * Time::DeltaTime());
			dir = 1;
		}

		if (vPos == GetPos())
		{
			if (prevDir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Leftt_Stay", true);
		}
		else
		{
			mOwner->SetDir(dir);
		}

		if (KEY(X, DOWN))
		{
			mState = eIceKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_X", true);
		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eIceKirby::IDLE;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"IceKirby_Right_Walk", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"IceKirby_Left_Walk", true);
			}
		}

		mOwner->SetPos(vPos);
		SetPos(vPos);
	}

	void IceKirby::skill(int dir)
	{
		if (KEY(X, UP))
		{
			mState = eIceKirby::IDLE;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
		}
	}

	void IceKirby::down(int dir)
	{
		if ((KEY(DOWN, UP)))
		{
			mState = eIceKirby::IDLE;
			SetScale(mOwner->GetScale());

			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
		}
	}

}