#include "zzIceKirby.h"
#include "zzTime.h"
#include "zzKey.h"
#include "zzIceSkill.h"
#include "zzPlayer.h"

namespace zz
{
	IceKirby::IceKirby(Player* owner)
		: Kirby(owner)
		, mAni(nullptr)
		, mState(eIceKirby::IDLE)
		, mPassedTime(0.f)
		, mbRun(false)

	{
	}

	IceKirby::~IceKirby()
	{
	}

	void IceKirby::Initialize()
	{
		
		mAni = GetOwner()->GetAni();

		Texture* IceKirby_Right_Walk = ResourceMgr::Load<Texture>(L"IceKirby_Right_Walk", L"..\\Resources\\IceKirby_Right_Walk.bmp");
		Texture* IceKirby_Left_Walk = ResourceMgr::Load<Texture>(L"IceKirby_Left_Walk", L"..\\Resources\\IceKirby_Left_Walk.bmp");
		
		Texture* IceKirby_Right = ResourceMgr::Load<Texture>(L"IceKirby_Right", L"..\\Resources\\IceKirby_Right.bmp");
		Texture* IceKirby_Left = ResourceMgr::Load<Texture>(L"IceKirby_Left", L"..\\Resources\\IceKirby_Left.bmp");

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Stay", Vector2(7.f, 4.f), Vector2(21.f, 25.f), Vector2(21.f, 0.f), 0.8f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Stay", Vector2(569.f, 4.f), Vector2(21.f, 25.f), Vector2(-21.f, 0.f), 0.8f, 2);

		mAni->CreateAnimation(IceKirby_Right_Walk, L"IceKirby_Right_Walk", Vector2(0.f, 0.f), Vector2(26.f, 27.f), Vector2(26.f, 0.f), 0.1f, 10);
		mAni->CreateAnimation(IceKirby_Left_Walk, L"IceKirby_Left_Walk", Vector2(234.f, 0.f), Vector2(26.f, 27.f), Vector2(-26.f, 0.f), 0.1f, 10);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Run", Vector2(0.f, 174.f), Vector2(25.f, 26.f), Vector2(25.f, 0.f), 0.043f, 8);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Run", Vector2(572.f, 174.f), Vector2(25.f, 26.f), Vector2(-25.f, 0.f), 0.043f, 8);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_X", Vector2(181.f, 573.f), Vector2(22.f, 27.f), Vector2(22.f, 0.f), 0.1f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_X", Vector2(394.f, 573.f), Vector2(22.f, 27.f), Vector2(-22.f, 0.f), 0.1f, 2);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Down", Vector2(7.f, 41.f), Vector2(25.f, 19.f), Vector2(25.f, 0.f), 0.8f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Down", Vector2(565.f, 41.f), Vector2(25.f, 19.f), Vector2(-25.f, 0.f), 0.8f, 2);

	}

	void IceKirby::Update()
	{
		int dir = GetOwner()->GetDir();

		switch (mState)
		{
		case IceKirby::eIceKirby::IDLE:
			idle(dir);
			break;

		case IceKirby::eIceKirby::WALK:
			walk(dir);
			break;

		case IceKirby::eIceKirby::RUN:
			run(dir);
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


	}


	void IceKirby::Enter()
	{
		int dir = GetOwner()->GetDir();

		mState = eIceKirby::IDLE;

		if (dir == 1)
		{
			mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
		}
		else
		{
			mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
		}
	}

	void IceKirby::Exit()
	{
	}

	void IceKirby::idle(int dir)
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
				mAni->PlayAnimation(L"IceKirby_Right_Run", true);
				mState = eIceKirby::RUN;
			}
			else if ((mbRun && dir == -1) && (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED)))
			{
				mAni->PlayAnimation(L"IceKirby_Left_Run", true);
				mState = eIceKirby::RUN;
			}
			else
			{
				if (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED))
				{
					mAni->PlayAnimation(L"IceKirby_Left_Walk", true);
				}
				else if (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED))
				{
					mAni->PlayAnimation(L"IceKirby_Right_Walk", true);
				}
				mState = eIceKirby::WALK;
			}
			
		}

		if (KEY(X, DOWN))
		{
			mState = eIceKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_X", true);

			IceSkill* ice = new IceSkill(GetOwner()->GetPos(), GetOwner()->GetDir());
			CreateObject(ice, eLayerType::SKILL);
		}


		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Down", true);
			GetOwner()->SetScale(Vector2(24.f, 15.f));

			mState = eIceKirby::DOWN;
		}

	}

	void IceKirby::walk(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
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

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);

		if (KEY(X, DOWN))
		{
			mState = eIceKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_X", true);

			IceSkill* ice = new IceSkill(vPos, dir);
			CreateObject(ice, eLayerType::SKILL);
		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eIceKirby::IDLE;
			mbRun = true;
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

	}

	void IceKirby::run(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
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

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);

		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eIceKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_X", true);

			IceSkill* ice = new IceSkill(vPos, dir);
			CreateObject(ice, eLayerType::SKILL);
		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eIceKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"IceKirby_Right_Run", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"IceKirby_Left_Run", true);
			}
		}
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
			GetOwner()->SetScale(Vector2(24.f, 24.f));

			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
		}
	}

}