#include "zzCutterKirby.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	CutterKirby::CutterKirby()
		: mAni(nullptr)
		, mColli(nullptr)
		, mbPressX(false)
		, mPassedTime(0.f)
		, mState(eCutterKirby::IDLE)
	{
	}

	CutterKirby::~CutterKirby()
	{
	}

	void CutterKirby::Initialize()
	{
		mColli = AddComponent<Collider>();
		mAni = AddComponent<Animator>();

		Texture* CutterKirby_Right = ResourceMgr::Load<Texture>(L"CutterKirby_Right", L"..\\Resources\\CutterKirby_Right.bmp");
		Texture* CutterKirby_Left = ResourceMgr::Load<Texture>(L"CutterKirby_Left", L"..\\Resources\\CutterKirby_Left.bmp");


		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Walk", Vector2(319.f, 21.f), Vector2(25.f, 27.f), Vector2(25.f, 0.f), 0.1f, 10);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_Walk", Vector2(245.f, 21.f), Vector2(25.f, 27.f), Vector2(-25.f, 0.f), 0.1f, 10);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Stay", Vector2(6.f, 20.f), Vector2(26.f, 25.f), Vector2(26.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_Stay", Vector2(557.f, 20.f), Vector2(26.f, 25.f), Vector2(-26.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Down", Vector2(33.f, 25.f), Vector2(25.f, 20.f), Vector2(25.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_Down", Vector2(531.f, 25.f), Vector2(25.f, 20.f), Vector2(-25.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_X", Vector2(175.f, 367.f), Vector2(42.f, 29.f), Vector2(42.f, 0.f), 0.08f, 6);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_X", Vector2(372.f, 367.f), Vector2(42.f, 29.f), Vector2(-42.f, 0.f), 0.08f, 6);


		GameObject::Initialize();
	}

	void CutterKirby::Update()
	{
		int dir = GetDir();

		switch (mState)
		{
		case CutterKirby::eCutterKirby::IDLE:
			idle(dir);
			break;

		case CutterKirby::eCutterKirby::MOVE:
			move(dir);
			break;

		case CutterKirby::eCutterKirby::SKILL:
			skill(dir);
			break;

		case CutterKirby::eCutterKirby::DOWN:
			down(dir);
			break;

		default:
			break;
		}

		Kirby::Update();
		GameObject::Update();
	}

	void CutterKirby::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void CutterKirby::Enter()
	{
		int dir = GetDir();

		mState = eCutterKirby::IDLE;

		if (dir == 1)
		{
			mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
		}
		else
		{
			mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);
		}
	}

	void CutterKirby::Exit()
	{
	}

	void CutterKirby::idle(int dir)
	{

		if (KEY(LEFT, DOWN) || KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED) || KEY(RIGHT, PRESSED))
		{
			mState = eCutterKirby::MOVE;

			if (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED))
			{
				mAni->PlayAnimation(L"CutterKirby_Left_Walk", true);
				dir = -1;
			}
			else if (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED))
			{
				mAni->PlayAnimation(L"CutterKirby_Right_Walk", true);
				dir = 1;
			}
			SetDir(dir);
		}

		if (KEY(X, DOWN))
		{
			mState = eCutterKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_X", true);
		}


		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_Down", true);
			SetScale(Vector2(24.f, 15.f));

			mState = eCutterKirby::DOWN;
		}
	
	} 

	void CutterKirby::move(int dir)
	{
		Vector2 vPos = GetPos();
		int prevDir = GetDir();

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
				mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);
		}
		else
		{
			SetDir(dir);
			SetPos(vPos);
		}

		if (KEY(X, DOWN))
		{
			mState = eCutterKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_X", true);
		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eCutterKirby::IDLE;
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"CutterKirby_Right_Walk", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"CutterKirby_Left_Walk", true);
			}
		}
	}

	void CutterKirby::skill(int dir)
	{
		mPassedTime += (float)Time::DeltaTime();
		if (mPassedTime >= 0.48f)
		{
			mPassedTime = 0.f;
			mState = eCutterKirby::MOVE;
		}
	}

	void CutterKirby::down(int dir)
	{
		if ((KEY(DOWN, UP)))
		{
			mState = eCutterKirby::IDLE;
			SetScale(Vector2(24.f, 24.f));
		}
	}
}