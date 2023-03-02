#include "zzFireSkill.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	FireSkill::FireSkill(Skill* owner)
		: mOwner(owner)
		, mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(36.f, 0.f))
		, mDir(1)
	{
	}

	FireSkill::~FireSkill()
	{
	}

	void FireSkill::Initialize()
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* mSkillTex = ResourceMgr::Load<Texture>(L"Fire_Skill_Right", L"..\\Resources\\Fire_Skill_Right.bmp");
		Texture* mSkillTex1 = ResourceMgr::Load<Texture>(L"Fire_Skill_Left", L"..\\Resources\\Fire_Skill_Left.bmp");

		mAni->CreateAnimation(mSkillTex, L"Fire_Skill_Right", Vector2(0.f, 0.f), Vector2(36.928f, 32.f), Vector2(36.928f, 0.f), 0.04f, 14);
		mAni->CreateAnimation(mSkillTex1, L"Fire_Skill_Left", Vector2(0.f, 0.f), Vector2(36.928f, 32.f), Vector2(36.928f, 0.f), 0.04f, 14);

		SetPos(Vector2(-20.f, -20.f));
		SetScale(Vector2(36.928f, 32.f));

		GameObject::Initialize();
		//temp = new Collider;
		//SetComponent<Collider>(temp);
	}

	void FireSkill::Update()
	{
		Vector2 vPos = GetPos();

		if (KEY(X, PRESSED))
		{
			vPos = mOwner->GetPos();
			mDir = mOwner->GetDir();

			if (mDir == 1)
			{
				vPos += mIntervalPos;
				mAni->PlayAnimation(L"Fire_Skill_Right", false);
			}
			else
			{
				vPos -= mIntervalPos;
				mAni->PlayAnimation(L"Fire_Skill_Left", false);
			}
		}

		if (KEY(X, UP))
		{
			mAni->StopAnimation(L"Fire_Skill_Left");
			mAni->StopAnimation(L"Fire_Skill_Right");
			vPos = Vector2(-20.f, -20.f);
		}

		SetPos(vPos);

		GameObject::Update();
	}

	void FireSkill::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}

	/*void FireSkill::Release()
	{
	}*/
}