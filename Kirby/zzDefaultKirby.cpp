#include "zzDefaultKirby.h"
#include "zzTime.h"
#include "zzKey.h"
#include "zzApplication.h"
namespace zz
{
	DefaultKirby::DefaultKirby()
		: mAni(nullptr)
		, mColli(nullptr)
		, mPassedTime(0.f)
		, mState(eDefaultKirby::IDLE)
		, mbPressX(false)
		, mbRun(false)
	{
	}

	DefaultKirby::~DefaultKirby()
	{
	}

	void DefaultKirby::Initialize()
	{
		mColli = AddComponent<Collider>();
		mAni = AddComponent<Animator>();

		SetLayerType(eLayerType::PLAYER);

		Texture* DefaultKirby_Right = ResourceMgr::Load<Texture>(L"DefaultKirby_Right", L"..\\Resources\\DefaultKirby_Right.bmp");
		Texture* DefaultKirby_Left = ResourceMgr::Load<Texture>(L"DefaultKirby_Left", L"..\\Resources\\DefaultKirby_Left.bmp");


		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Walk", Vector2(253.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.1f, 10);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Walk", Vector2(726.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.1f, 10);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Run", Vector2(569.f, 306.f), Vector2(24.f, 19.f), Vector2(24.f, 0.f), 0.043f, 8);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Run", Vector2(407.f, 306.f), Vector2(24.f, 19.f), Vector2(-24.f, 0.f), 0.043f, 8);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Stay", Vector2(8.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Stay", Vector2(972.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Down", Vector2(31.f, 19.f), Vector2(25.f, 10.f), Vector2(25.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Down", Vector2(944.f, 19.f), Vector2(25.f, 10.f), Vector2(-25.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_X_1", Vector2(796.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.08f, 2);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_X_1", Vector2(181.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.08f, 2);
		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_X_2", Vector2(842.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.08f, 2);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_X_2", Vector2(135.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.08f, 2);

		mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);

		mAni->GetEndEvent(L"DefaultKirby_Right_Walk") = std::bind(&DefaultKirby::jump, this);

		Camera::SetTarget(this);

		GameObject::Initialize();

		KirbyInitialize(this);
	}

	void DefaultKirby::Update()
	{
		int dir = GetDir();

		switch (mState)
		{
		case DefaultKirby::eDefaultKirby::IDLE:
			idle(dir);
			break;

		case DefaultKirby::eDefaultKirby::WALK:
			walk(dir);
			break;

		case DefaultKirby::eDefaultKirby::RUN:
			run(dir);
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

		Kirby::Update();
		GameObject::Update();
	}

	void DefaultKirby::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DefaultKirby::Enter()
	{
		int dir = GetDir();

		mState = eDefaultKirby::IDLE;

		if (dir == 1)
		{
			mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
		}
		else
		{
			mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}
	}

	void DefaultKirby::Exit()
	{

	}

	void DefaultKirby::idle(int dir)
	{
		if (mbRun)
		{
			mPassedTime += (float)Time::DeltaTime();

			if (mPassedTime > 0.2f)
			{
				mbRun = false;
				mPassedTime = 0.f;
			}
		}

		if (KEY(LEFT, DOWN) || KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED) || KEY(LEFT, PRESSED))
		{

			if ((mbRun && dir == 1) && (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED)))
			{
					mAni->PlayAnimation(L"DefaultKirby_Right_Run", true);
					mState = eDefaultKirby::RUN;
			}
			else if ((mbRun && dir == -1) && (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED)))
			{
					mAni->PlayAnimation(L"DefaultKirby_Left_Run", true);
					mState = eDefaultKirby::RUN;
			}
			else
			{
				if (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED))
				{
					mAni->PlayAnimation(L"DefaultKirby_Left_Walk", true);
				}
				else if (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED))
				{
					mAni->PlayAnimation(L"DefaultKirby_Right_Walk", true);
				}
				mState = eDefaultKirby::WALK;
			}

		}

		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);
			mbPressX = true;
		}


		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Down", true);
			SetScale(Vector2(24.f, 15.f));

			mState = eDefaultKirby::DOWN;
		}

	}

	void DefaultKirby::walk(int dir)
	{
		Vector2 vPos = GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}

		else if (KEY(LEFT, PRESSED))
		{
			vPos.x -= (float)(100.f * Time::DeltaTime());
			dir = -1;
		}

		else if (KEY(RIGHT, PRESSED))
		{
			vPos.x += (float)(100.f * Time::DeltaTime());
			dir = 1;
		}

		SetDir(dir);
		SetPos(vPos);

		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);
		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eDefaultKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"DefaultKirby_Right_Walk", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"DefaultKirby_Left_Walk", true);
			}
		}

	}

	void DefaultKirby::run(int dir)
	{
		Vector2 vPos = GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}

		else if (KEY(LEFT, PRESSED))
		{
			vPos.x -= (float)(150.f * Time::DeltaTime());
			dir = -1;
		}

		else if (KEY(RIGHT, PRESSED))
		{
			vPos.x += (float)(150.f * Time::DeltaTime());
			dir = 1;
		}

		SetDir(dir);
		SetPos(vPos);

		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);
		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eDefaultKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"DefaultKirby_Right_Run", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"DefaultKirby_Left_Run", true);
			}
		}

	}

	void DefaultKirby::skill(int dir)
	{
		mPassedTime += (float)Time::DeltaTime();

		if (mbPressX)
		{
			if (mPassedTime >= 1.f)
			{
				if (dir == 1)
					mAni->PlayAnimation(L"DefaultKirby_Right_X_2", true);
				else
					mAni->PlayAnimation(L"DefaultKirby_Left_X_2", true);
				mbPressX = false;
			}
		}

		if (KEY(X, UP))
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::IDLE;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}
	}

	void DefaultKirby::down(int dir)
	{
		if ((KEY(DOWN, UP)))
		{
			mState = eDefaultKirby::IDLE;
			SetScale(Vector2(24.f, 24.f));

			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}
	}
	void DefaultKirby::jump()
	{
	
	}
}