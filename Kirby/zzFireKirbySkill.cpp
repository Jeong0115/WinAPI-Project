#include "zzFireKirbySkill.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	FireKirbySkill::FireKirbySkill()
		: mDir(1)
		, obj(nullptr)
		, mTr(nullptr)
		, mAni(nullptr)
		, mColli(nullptr)
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

		mTr->SetPos(Vector2(-20.f, -20.f));
		mTr->SetScale(Vector2(36.928f, 32.f));
		mAni->SetPos(mTr->GetPos());
		mColli->SetPos(mTr->GetPos());
		mColli->SetScale(mTr->GetScale());

		
		//temp = new Collider;
		//SetComponent<Collider>(temp);
	}

	void FireKirbySkill::Update()
	{

		//int prevDir = mDir;

		

		if (KEY(LEFT, PRESSED))
		{
			mDir = -1;
		}

		if (KEY(RIGHT, PRESSED))
		{
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
			//SetComponent<Collider>(mColli);
			mTr->SetPos(obj->GetComponent<Transform>()->GetPos());
			if (mDir == 1)
			{
				mTr->SetPos(Vector2(mTr->GetPos().x + 30.f, mTr->GetPos().y));
				mAni->PlayAnimation(L"FireSkill", true);
			}
			else
			{
				mTr->SetPos(Vector2(mTr->GetPos().x - 30.f, mTr->GetPos().y));
				mAni->PlayAnimation(L"FireSkill1", true);
			}
		}

		if (KEY(X, UP))
		{
			mAni->StopAnimation(L"FireSkill1");
			mAni->StopAnimation(L"FireSkill");
			mTr->SetPos(Vector2(-20.f, -20.f));
			//SetComponent<Collider>(temp);
		}

		//if (prevDir != mDir)
		//{
		//	if (mDir == 1)
		//		vPos.x += 60.f;
		//	else
		//		vPos.x -= 60.f;
		//}

		mColli->SetPos(mTr->GetPos());
		//mTr->SetPos(vPos);
		mAni->SetPos(mTr->GetPos());

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