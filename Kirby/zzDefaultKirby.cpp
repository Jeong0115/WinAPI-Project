#include "zzDefaultKirby.h"
#include "zzTime.h"
#include "zzKey.h"
#include "zzApplication.h"
#include "zzDefaultSkill.h"
#include "zzKirby.h"
#include "zzPlayer.h"
#include "zzGameObject.h"

namespace zz
{
	DefaultKirby::DefaultKirby(Player* owner)
		: Kirby(owner)
		, mPassedTime(0.f)
		, mState(eDefaultKirby::IDLE)
		, mbPressX(false)
		, mbRun(false)
		, mInvincibleTime(0.f)
		, mAni(nullptr)
	{
	}

	DefaultKirby::~DefaultKirby()
	{
	}

	void DefaultKirby::Initialize()
	{
		mAni = GetOwner()->GetAni();


		Texture* DefaultKirby_Right = ResourceMgr::Load<Texture>(L"DefaultKirby_Right", L"..\\Resources\\DefaultKirby_Right.bmp");
		Texture* DefaultKirby_Left = ResourceMgr::Load<Texture>(L"DefaultKirby_Left", L"..\\Resources\\DefaultKirby_Left.bmp");


		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Walk", Vector2(253.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.1f, 10);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Walk", Vector2(726.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.1f, 10);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Run", Vector2(569.f, 306.f), Vector2(24.f, 19.f), Vector2(24.f, 0.f), 0.043f, 8);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Run", Vector2(407.f, 306.f), Vector2(24.f, 19.f), Vector2(-24.f, 0.f), 0.043f, 8);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Damage", Vector2(0.f, 179.f), Vector2(22.f, 22.f), Vector2(22.f, 0.f), 0.04f, 10);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Damage", Vector2(978.f, 179.f), Vector2(22.f, 22.f), Vector2(-22.f, 0.f), 0.04f, 10);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Stay", Vector2(8.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Stay", Vector2(972.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Down", Vector2(31.f, 19.f), Vector2(25.f, 10.f), Vector2(25.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Down", Vector2(944.f, 19.f), Vector2(25.f, 10.f), Vector2(-25.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_X_1", Vector2(796.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.08f, 2);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_X_1", Vector2(181.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.08f, 2);
		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_X_2", Vector2(842.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.08f, 2);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_X_2", Vector2(135.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.08f, 2);

		mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);

		mAni->GetCompleteEvent(L"DefaultKirby_Right_Damage") = std::bind(&DefaultKirby::active, this);
		mAni->GetCompleteEvent(L"DefaultKirby_Left_Damage") = std::bind(&DefaultKirby::active, this);
	}

	void DefaultKirby::Update()
	{
		int dir = GetOwner()->GetDir();

		if (GetOwner()->GetState() == eState::INVINCIBLE)
		{
			mInvincibleTime += (float)Time::DeltaTime();

			if (mInvincibleTime > 2.2f)
			{
				GetOwner()->SetState(eState::ACTIVE);
				mInvincibleTime = 0.f;
			}
		}

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

		case DefaultKirby::eDefaultKirby::DAMAGE:
			damage(dir);
			break;

		default:
			break;
		}

	}

	void DefaultKirby::Enter()
	{
		int dir = GetOwner()->GetDir();

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
		
			DefaultSkill* nomarl = new DefaultSkill(GetOwner()->GetPos(), GetOwner()->GetDir());
			nomarl->SetOwner(GetOwner());
			CreateObject(nomarl, eLayerType::INHALE);
		}


		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Down", true);
			GetOwner()->SetScale(Vector2(24.f, 15.f));

			mState = eDefaultKirby::DOWN;
		}

	}

	void DefaultKirby::walk(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

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


		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);

		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);

			DefaultSkill* nomarl = new DefaultSkill(vPos, dir);
			nomarl->SetOwner(GetOwner());
			CreateObject(nomarl, eLayerType::INHALE);
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
		Vector2 vPos = GetOwner()->GetPos();

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

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);

		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);

			DefaultSkill* nomarl = new DefaultSkill(vPos, dir);
			nomarl->SetOwner(GetOwner());
			CreateObject(nomarl, eLayerType::INHALE);
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
			GetOwner()->SetScale(Vector2(24.f, 24.f));

			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}
	}

	void DefaultKirby::damage(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();
		if (dir == 1)
		{
			vPos.x -= (float)(150.f * Time::DeltaTime());
		}
		else
		{
			vPos.x += (float)(150.f * Time::DeltaTime());
		}
		GetOwner()->SetPos(vPos);
	}

	void DefaultKirby::inhale(int dir)
	{

	}

	void DefaultKirby::active()
	{
		int dir = GetOwner()->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
		}
		else
		{
			mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}
		mState = eDefaultKirby::IDLE;
		//SetState(eState::ACTIVE);
	}
	void DefaultKirby::OnCollisionEnter()
	{
		int dir = GetOwner()->GetDir();
		if (dir == 1)
			mAni->PlayAnimation(L"DefaultKirby_Right_Damage", false);
		else
			mAni->PlayAnimation(L"DefaultKirby_Left_Damage", false);

		mState = eDefaultKirby::DAMAGE;
		GetOwner()->SetState(eState::INVINCIBLE);
	}


}