#include "zzFireKirby.h"
#include "zzTime.h"
#include "zzKey.h"

#include "zzFireSkill.h"
#include "zzFireDashSkill.h"

namespace zz
{
	FireKirby::FireKirby()
		: mAni(nullptr)
		, mState(eFireKirby::IDLE)
		, mPassedTime(0.f)
		, mbRun(false)
	{
	}

	FireKirby::~FireKirby()
	{
	}

	void FireKirby::Initialize()
	{
		mAni = AddComponent<Animator>();

		Texture* FireKirby_Right = ResourceMgr::Load<Texture>(L"FireKirby_Right", L"..\\Resources\\FireKirby_Right.bmp");
		Texture* FireKirby_Left = ResourceMgr::Load<Texture>(L"FireKirby_Left", L"..\\Resources\\FireKirby_Left.bmp");

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Stay", Vector2(8.f, 4.f), Vector2(23.f, 32.f), Vector2(23.f, 0.f), 0.08f, 8);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Stay", Vector2(663.f, 4.f), Vector2(23.f, 32.f), Vector2(-23.f, 0.f), 0.08f, 8);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Down", Vector2(230.f, 10.f), Vector2(27.f, 26.f), Vector2(27.f, 0.f), 0.08f, 8);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Down", Vector2(437.f, 10.f), Vector2(27.f, 26.f), Vector2(-27.f, 0.f), 0.08f, 8);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Walk", Vector2(7.f, 292.f), Vector2(25.f, 36.f), Vector2(25.f, 0.f), 0.05f, 20);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Walk", Vector2(662.f, 292.f), Vector2(25.f, 36.f), Vector2(-25.f, 0.f), 0.05f, 20);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Run", Vector2(0.f, 342.f), Vector2(48.f, 30.f), Vector2(48.f, 0.f), 0.043f, 8);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Run", Vector2(646.f, 342.f), Vector2(48.f, 30.f), Vector2(-48.f, 0.f), 0.043f, 8);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_X", Vector2(187.f, 1109.f), Vector2(31.f, 29.f), Vector2(31.f, 0.f), 0.05f, 4);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_X", Vector2(476.f, 1109.f), Vector2(31.f, 29.f), Vector2(-31.f, 0.f), 0.05f, 4);


		SetScale(Kirby::GetKirbyScale());
		GameObject::Initialize();
	}

	void FireKirby::Update()
	{
		int dir = GetDir();

		switch (mState)
		{
		case FireKirby::eFireKirby::IDLE:
			idle(dir);
			break;

		case FireKirby::eFireKirby::WALK:
			walk(dir);
			break;

		case FireKirby::eFireKirby::RUN:
			run(dir);
			break;



		case FireKirby::eFireKirby::SKILL:
			skill(dir);
			break;

		case FireKirby::eFireKirby::DASHSKILL:
			dashSkill(dir);
			break;

		case FireKirby::eFireKirby::DOWN:
			down(dir);
			break;

		default:
			break;
		}

		//Kirby::Update();
		GameObject::Update();
	}

	void FireKirby::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FireKirby::Enter()
	{
		int dir = GetDir();

		mState = eFireKirby::IDLE;

		if (dir == 1)
		{
			mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
		}
		else
		{
			mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
		}
	}

	void FireKirby::Exit()
	{
	}

	void FireKirby::idle(int dir)
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
				mAni->PlayAnimation(L"FireKirby_Right_Run", true);
				mState = eFireKirby::RUN;
			}
			else if ((mbRun && dir == -1) && (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED)))
			{
				mAni->PlayAnimation(L"FireKirby_Left_Run", true);
				mState = eFireKirby::RUN;
			}
			else
			{
				if (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED))
				{
					mAni->PlayAnimation(L"FireKirby_Left_Walk", true);
				}
				else if (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED))
				{
					mAni->PlayAnimation(L"FireKirby_Right_Walk", true);
				}
				mState = eFireKirby::WALK;
			}
			
		}

		if (KEY(X, DOWN))
		{
			mState = eFireKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_X", true);
		
			FireSkill* fire = new FireSkill(GetPos(), GetDir());
			CreateObject(fire, eLayerType::SKILL);
		}


		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Down", true);
			SetScale(Vector2(24.f, 15.f));

			mState = eFireKirby::DOWN;
		}

	}

	void FireKirby::walk(int dir)
	{
		Vector2 vPos = GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
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
			mState = eFireKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_X", true);
		}

		SetDir(dir);
		SetPos(vPos);

		if (KEY(X, DOWN))
		{
			mState = eFireKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_X", true);

			FireSkill* fire = new FireSkill(GetPos(), GetDir());
			CreateObject(fire, eLayerType::SKILL);
		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eFireKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"FireKirby_Right_Walk", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"FireKirby_Left_Walk", true);
			}
		}
	}

	

	void FireKirby::run(int dir)
	{
		Vector2 vPos = GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
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
			mState = eFireKirby::DASHSKILL;
			mAni->StopAnimation();

			SetState(eState::INVINCIBLE);
			FireDashSkill* fire = new FireDashSkill(GetPos(), GetDir());
			fire->SetOwner(this);
			CreateObject(fire, eLayerType::SKILL);
		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eFireKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"FireKirby_Right_Run", true);
			}
			else if (KEY(RIGHT, UP))
			{	
				mAni->PlayAnimation(L"FireKirby_Left_Run", true);
			}
		}
	}

	void FireKirby::skill(int dir)
	{
		if (KEY(X, UP))
		{
			mState = eFireKirby::IDLE;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
		}
	}

	void FireKirby::dashSkill(int dir)
	{
		Vector2 vPos = GetPos();
		mPassedTime += (float)Time::DeltaTime();

		if (mPassedTime > 1.2f)
		{
			mState = eFireKirby::IDLE;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);

			mPassedTime = 0.f;
			SetState(eState::ACTIVE);
		}
		else
		{
			if (dir == 1)
			{
				vPos.x += (float)(200.f * Time::DeltaTime());
			}
			else
			{
				vPos.x -= (float)(200.f * Time::DeltaTime());
			}
		}

		SetPos(vPos);
	}

	void FireKirby::down(int dir)
	{
		if ((KEY(DOWN, UP)))
		{
			mState = eFireKirby::IDLE;
			SetScale(Vector2(24.f, 24.f));

			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
		}
	}

}