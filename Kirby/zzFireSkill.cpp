#include "zzFireSkill.h"
#include "zzTexture.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	FireSkill::FireSkill(Vector2 pos, int dir)
		: mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(48.f, 7.f))
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* Fire_Skill_Right = ResourceMgr::Load<Texture>(L"Fire_Skill_Right", L"..\\Resources\\Fire_Skill_Right.bmp");
		Texture* Fire_Skill_Left = ResourceMgr::Load<Texture>(L"Fire_Skill_Left", L"..\\Resources\\Fire_Skill_Left.bmp");

		mAni->CreateAnimation(Fire_Skill_Right, L"Fire_Skill_Right", Vector2(816.f, 0.f), Vector2(68.f, 39.f), Vector2(-68.f, 0.f), 0.03f, 13);
		mAni->CreateAnimation(Fire_Skill_Left, L"Fire_Skill_Left", Vector2(0.f, 0.f), Vector2(68.f, 39.f), Vector2(68.f, 0.f), 0.03f, 13);

		SetScale(Vector2(68.f, 39.f));

		pos.y += mIntervalPos.y;
		if (dir == 1)
		{
			pos.x += mIntervalPos.x;
			mAni->PlayAnimation(L"Fire_Skill_Right", true);
		}
		else
		{
			pos.x -= mIntervalPos.x;
			mAni->PlayAnimation(L"Fire_Skill_Left", true);
		}
		SetPos(pos);
	}

	FireSkill::~FireSkill()
	{
	}

	void FireSkill::Initialize()
	{
	}

	void FireSkill::Update()
	{
	
		if (KEY(X, UP))
		{
			DeleteObject(this, GetLayerType());
		}


		GameObject::Update();
	}

	void FireSkill::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}

}