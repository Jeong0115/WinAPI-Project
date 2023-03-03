#include "zzDefaultSkill.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	DefaultSkill::DefaultSkill(Skill* owner)
		: mOwner(owner)
		, mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(30.f, 12.f))
		, mDir(1)
	{
	}

	DefaultSkill::~DefaultSkill()
	{
	}

	void DefaultSkill::Initialize()
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* tornado_Right = ResourceMgr::Load<Texture>(L"tornado_Right", L"..\\Resources\\tornado.bmp");
		Texture* tornado_Left = ResourceMgr::Load<Texture>(L"tornado_Left", L"..\\Resources\\tornado_Left.bmp");

		mAni->CreateAnimation(tornado_Right, L"tornado_Right", Vector2(0.f, 0.f), Vector2(36.5f, 45.f), Vector2(36.5f, 0.f), 0.05f, 4);
		mAni->CreateAnimation(tornado_Left, L"tornado_Left", Vector2(109.5f, 0.f), Vector2(36.5f, 45.f), Vector2(-36.5f, 0.f), 0.05f, 4);

		SetPos(Vector2(-20.f, -20.f));
		SetScale(Vector2(36.5f, 45.f));

		GameObject::Initialize();
	}

	void DefaultSkill::Update()
	{
		Vector2 vPos = GetPos();

		if (KEY(X, PRESSED))
		{
			vPos = mOwner->GetPos();
			mDir = mOwner->GetDir();

			if (mDir == 1)
			{
				vPos += mIntervalPos;
				mAni->PlayAnimation(L"tornado_Right", false);
			}
			else
			{
				vPos.x -= mIntervalPos.x;
				vPos.y += mIntervalPos.y;
				mAni->PlayAnimation(L"tornado_Left", false);
			}
		}

		if (KEY(X, UP))
		{
			mAni->StopAnimation(L"tornado_Right");
			mAni->StopAnimation(L"tornado_Left");
			vPos = Vector2(-20.f, -20.f);
		}

		SetPos(vPos);

		GameObject::Update();
	}

	void DefaultSkill::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	/*void DefaultSkill::Release()
	{
	}*/
}