#include "zzCutterSkill.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	CutterSkill::CutterSkill(Vector2 pos, int dir)
		: mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(36.f, 0.f))
		, mbPressX(false)
		, mPassedTime(0.f)
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* CutterKirby_Right = ResourceMgr::Load<Texture>(L"CutterKirby_Right", L"..\\Resources\\CutterKirby_Right.bmp");
		Texture* CutterKirby_Left = ResourceMgr::Load<Texture>(L"CutterKirby_Left", L"..\\Resources\\CutterKirby_Left.bmp");

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_X", Vector2(200.f, 411.f), Vector2(42.f, 32.f), Vector2(42.f, 0.f), 0.01f, 4);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_X", Vector2(347.f, 411.f), Vector2(42.f, 32.f), Vector2(-42.f, 0.f), 0.01f, 4);

		SetScale(Vector2(42.f, 32.f));

		if (dir == 1)
		{
			pos += mIntervalPos;
			mAni->PlayAnimation(L"CutterKirby_Right_X", true);
		}
		else
		{
			pos -= mIntervalPos;
			mAni->PlayAnimation(L"CutterKirby_Left_X", true);
		}
		SetPos(pos);
		SetDir(dir);
	}

	CutterSkill::~CutterSkill()
	{
	}

	void CutterSkill::Initialize()
	{
	}

	void CutterSkill::Update()
	{
		Vector2 vPos = GetPos();
		int dir = GetDir();

		mPassedTime += (float)Time::DeltaTime();

		if (mPassedTime <= 0.4f)
		{
			vPos.x += (float)(200.f * Time::DeltaTime()) * dir;
			vPos.y -= (float)(50.f * Time::DeltaTime());
		}
		else if (mPassedTime <= 0.8f)
		{
			vPos.x -= (float)(500.f * Time::DeltaTime()) * dir;
			vPos.y -= (float)(50.f * Time::DeltaTime());
		}
		else if(!IsDead())
		{
			DeleteObject(this, GetLayerType());
		}
		SetPos(vPos);
		SetDir(dir);
	
		GameObject::Update();
	}

	void CutterSkill::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}

}