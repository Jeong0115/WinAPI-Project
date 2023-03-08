#include "zzDefaultSkill.h"
#include "zzTime.h"
#include "zzKey.h"


namespace zz
{
	DefaultSkill::DefaultSkill(Vector2 pos, int dir)
		: mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(30.f, 12.f))
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* tornado_Right = ResourceMgr::Load<Texture>(L"tornado_Right", L"..\\Resources\\tornado.bmp");
		Texture* tornado_Left = ResourceMgr::Load<Texture>(L"tornado_Left", L"..\\Resources\\tornado_Left.bmp");

		mAni->CreateAnimation(tornado_Right, L"tornado_Right", Vector2(0.f, 0.f), Vector2(36.5f, 45.f), Vector2(36.5f, 0.f), 0.05f, 4);
		mAni->CreateAnimation(tornado_Left, L"tornado_Left", Vector2(109.5f, 0.f), Vector2(36.5f, 45.f), Vector2(-36.5f, 0.f), 0.05f, 4);

		SetScale(Vector2(36.5f, 45.f));

		

		if (dir == 1)
		{
			pos += mIntervalPos;
			mAni->PlayAnimation(L"tornado_Right", true);
		}
		else
		{
			pos.x -= mIntervalPos.x;
			pos.y += mIntervalPos.y;
			mAni->PlayAnimation(L"tornado_Left", true);
		}
		SetPos(pos);
	}

	DefaultSkill::~DefaultSkill()
	{
	}

	void DefaultSkill::Initialize()
	{
	}

	void DefaultSkill::Update()
	{
	
		if (KEY(X, UP))
		{
			DeleteObject(this, GetLayerType());
		}

		GameObject::Update();
	}

	void DefaultSkill::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}