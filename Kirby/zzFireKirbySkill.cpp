#include "zzFireKirbySkill.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	FireKirbySkill::FireKirbySkill()
		: mDir(1)
	{
	}
	FireKirbySkill::~FireKirbySkill()
	{
	}

	void FireKirbySkill::Initialize()
	{
		GameObject::Initialize();

		mTr = AddComponent<Transform>();
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* mSkillTex = ResourceMgr::Load<Texture>(L"FireSkill", L"..\\Resources\\FireKirby_Skill.bmp");
		Texture* mSkillTex1 = ResourceMgr::Load<Texture>(L"FireSkill1", L"..\\Resources\\FireKirby_Skill1.bmp");

		mAni->CreateAnimation(mSkillTex, L"FireSkill", Vector2(0.f, 0.f), Vector2(36.928f, 32.f), Vector2(36.928f, 0.f), 0.04f, 14);
		mAni->CreateAnimation(mSkillTex1, L"FireSkill1", Vector2(0.f, 0.f), Vector2(36.928f, 32.f), Vector2(36.928f, 0.f), 0.04f, 14);

		mTr->SetPos(Vector2(40.f, 135.f));
		mTr->SetScale(Vector2(36.928f, 32.f));
		mAni->SetPos(mTr->GetPos());
		mColli->SetPos(mTr->GetPos());
		mColli->SetScale(mTr->GetScale());


		temp = new Collider;
		SetComponent<Collider>(temp);
	}

	void FireKirbySkill::Update()
	{

		int prevDir = mDir;
		Vector2 vPos = mTr->GetPos();


		

		if (KEY(LEFT, PRESSED))
		{
			vPos.x -= 100.f * Time::DeltaTime();
			mDir = -1;
		}

		if (KEY(RIGHT, PRESSED))
		{
			vPos.x += 100.f * Time::DeltaTime();
			mDir = 1;
		}

		//if (KEY(UP, PRESSED))
		//{
		//	vPos.y -= 100.f * Time::DeltaTime();
		//}

		//if (KEY(DOWN, PRESSED))
		//{
		//	vPos.y += 100.f * Time::DeltaTime();
		//}

		if (KEY(X, PRESSED))
		{
			SetComponent<Collider>(mColli);
			if (mDir == 1)
			{
				mAni->PlayAnimation(L"FireSkill", true);
			}
			else
			{
				mAni->PlayAnimation(L"FireSkill1", true);
			}
		}

		if (KEY(X, UP))
		{
			mAni->StopAnimation(L"FireSkill1");
			mAni->StopAnimation(L"FireSkill");

			SetComponent<Collider>(temp);
		}

		if (prevDir != mDir)
		{
			if (mDir == 1)
				vPos.x += 60.f;
			else
				vPos.x -= 60.f;
		}

		mColli->SetPos(vPos);
		mTr->SetPos(vPos);
		mAni->SetPos(vPos);

		GameObject::Update();
	}

	void FireKirbySkill::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}

	void FireKirbySkill::Release()
	{
	}
}