#include "zzDefaultKirby.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	DefaultKirby::DefaultKirby(Kirby* owner)
		: mOwner(owner)
		, mAni(nullptr)
		, mColli(nullptr)
		, mPassedTime(0.f)
		, mState(eDefaultKirby::IDLE)
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

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Down", Vector2(31.f, 19.f), Vector2(25.f, 10.f), Vector2(25.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Down", Vector2(944.f, 19.f), Vector2(25.f, 10.f), Vector2(-25.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_X_1", Vector2(796.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.08f, 2);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_X_1", Vector2(181.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.08f, 2);
		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_X_2", Vector2(842.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.08f, 2);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_X_2", Vector2(135.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.08f, 2);

		SetPos(mOwner->GetPos());
		SetScale(mOwner->GetScale());

		GameObject::Initialize();
	}

	void DefaultKirby::Update()
	{
		int dir = mOwner->GetDir();

		switch (mState)
		{
		case DefaultKirby::eDefaultKirby::IDLE:
			idle(dir);
			break;

		case DefaultKirby::eDefaultKirby::MOVE:
			move(dir);
			break;

		case DefaultKirby::eDefaultKirby::SKILL:
			skill(dir);
			break;

		case DefaultKirby::eDefaultKirby::DOWN:
			down(dir);
			break;

		default:
			break;
		}

		GameObject::Update();
	}

	void DefaultKirby::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DefaultKirby::idle(int dir)
	{
		if (dir == 1)
			mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
		else
			mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);

		if (KEY(LEFT, DOWN) || KEY(RIGHT, DOWN))
		{
			mState = eDefaultKirby::MOVE;
			//move(dir);
		}

		if (KEY(X, DOWN))
		{
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);
			//skill(dir);
		}


		if (KEY(DOWN, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Down", true);
			SetScale(Vector2(24.f, 15.f));

			mState = eDefaultKirby::DOWN;
			//down(dir);
		}

	}

	void DefaultKirby::move(int dir)
	{
		Vector2 vPos = mOwner->GetPos();
		int prevDir = mOwner->GetDir();

		if (KEY(LEFT, PRESSED))
		{
			vPos.x -= (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(L"DefaultKirby_Left_Walk", true);
			dir = -1;
		}

		if (KEY(RIGHT, PRESSED))
		{
			vPos.x += (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(L"DefaultKirby_Right_Walk", true);
			dir = 1;
		}

		if (vPos == GetPos())
		{
			if (prevDir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}
		else
		{
			mOwner->SetDir(dir);
		}

		if (KEY(X, DOWN))
		{
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);
			//skill(dir);
		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
			//&& !(KEY(LEFT, DOWN)) && !(KEY(RIGHT, DOWN)))
		{
			mState = eDefaultKirby::IDLE;
			//idle(dir);
		}

		mOwner->SetPos(vPos);
		SetPos(vPos);
	}

	void DefaultKirby::skill(int dir)
	{
		mPassedTime += (float)Time::DeltaTime();
		if (mPassedTime <= 1.f)
		{
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);
		}
		else
		{
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_2", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_2", true);
		}

		if (KEY(X, UP))
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::MOVE;
		}
	}

	void DefaultKirby::down(int dir)
	{
		if ((KEY(DOWN, UP)))
		{
			mState = eDefaultKirby::IDLE;
			SetScale(mOwner->GetScale());
			//idle(dir);
		}
	}
}