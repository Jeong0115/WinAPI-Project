#include "zzCutterKirby.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	CutterKirby::CutterKirby(Kirby* owner)
		: mOwner(owner)
		, mAni(nullptr)
		, mColli(nullptr)
		, mbPressX(false)
		, mPassedTime(0.f)
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

		SetPos(mOwner->GetPos());
		SetScale(mOwner->GetScale());

		GameObject::Initialize();
	}

	void CutterKirby::Update()
	{
		Vector2 vPos = GetPos();

		int dir = mOwner->GetDir();

		if (mbPressX)
		{
			mPassedTime += (float)Time::DeltaTime();
			if (mPassedTime >= 0.48f)
			{
				mPassedTime = 0.f;
				mbPressX = false;
			/*	if (dir == 1)
					mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
				else
					mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);*/
			}
		}
		else
		{
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);



			if (KEY(LEFT, PRESSED))
			{
				vPos.x -= (float)(100.f * Time::DeltaTime());
				mAni->PlayAnimation(L"CutterKirby_Left_Walk", true);
				dir = -1;
			}

			if (KEY(RIGHT, PRESSED))
			{
				vPos.x += (float)(100.f * Time::DeltaTime());
				mAni->PlayAnimation(L"CutterKirby_Right_Walk", true);
				dir = 1;
			}

			if (KEY(DOWN, PRESSED))
			{
				if (dir == 1)
					mAni->PlayAnimation(L"CutterKirby_Right_Down", true);
				else
					mAni->PlayAnimation(L"CutterKirby_Left_Down", true);
				SetScale(Vector2(24.f, 15.f));
			}

			if (KEY(DOWN, UP))
			{
				SetScale(mOwner->GetScale());
			}

			if (KEY(X, DOWN))
			{
				if (dir == 1)
					mAni->PlayAnimation(L"CutterKirby_Right_X", false);
				else
					mAni->PlayAnimation(L"CutterKirby_Left_X", false);
				mPassedTime = 0.f;
				mbPressX = true;
			}
		}

		mOwner->SetPos(vPos);
		mOwner->SetDir(dir);
		SetPos(vPos);

		GameObject::Update();

	}

	void CutterKirby::Render(HDC hdc)
	{

		GameObject::Render(hdc);

	}
}