#include "zzCutterSkill.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	CutterSkill::CutterSkill(Skill* owner)
		: mOwner(owner)
		, mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(36.f, 0.f))
		, mDir(1)
		, mbPressX(false)
		, mPassedTime(0.f)
	{
	}

	CutterSkill::~CutterSkill()
	{
	}

	void CutterSkill::Initialize()
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* CutterKirby_Right = ResourceMgr::Load<Texture>(L"CutterKirby_Right", L"..\\Resources\\CutterKirby_Right.bmp");
		Texture* CutterKirby_Left = ResourceMgr::Load<Texture>(L"CutterKirby_Left", L"..\\Resources\\CutterKirby_Left.bmp");

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_X", Vector2(200.f, 411.f), Vector2(42.f, 32.f), Vector2(42.f, 0.f), 0.01f, 4);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_X", Vector2(347.f, 411.f), Vector2(42.f, 32.f), Vector2(-42.f, 0.f), 0.01f, 4);

		SetPos(Vector2(-20.f, -20.f));
		SetScale(Vector2(42.f, 32.f));

		GameObject::Initialize();
		//temp = new Collider;
		//SetComponent<Collider>(temp);
	}

	void CutterSkill::Update()
	{
		Vector2 vPos = GetPos();

		if(mbPressX)
		{
			mPassedTime += (float)Time::DeltaTime();

			if(mPassedTime <= 0.4f)
			{
				vPos.x += (float)(200.f * Time::DeltaTime()) * mDir;
				vPos.y -= (float)(50.f * Time::DeltaTime());
			}
			else if (mPassedTime <= 0.8f)
			{
				vPos.x -= (float)(500.f * Time::DeltaTime()) * mDir;
				vPos.y -= (float)(50.f * Time::DeltaTime());
			}
			else
			{
				mPassedTime = 0.f;
				mbPressX = false;
				mAni->StopAnimation(L"CutterKirby_Right_X");
				mAni->StopAnimation(L"CutterKirby_Left_X");
				vPos = Vector2(-20.f, -20.f);
			}
		}
		else
		{
			if (KEY(X, DOWN))
			{
				vPos = mOwner->GetPos();
				mDir = mOwner->GetDir();

				if (mDir == 1)
				{
					vPos += mIntervalPos;
					mAni->PlayAnimation(L"CutterKirby_Right_X", true);
				}
				else
				{
					vPos -= mIntervalPos;
					mAni->PlayAnimation(L"CutterKirby_Left_X", true);
				}
				mbPressX = true;
			}
		}
		
		SetPos(vPos);

		GameObject::Update();
	}

	void CutterSkill::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}

	/*void FireSkill::Release()
	{
	}*/
}