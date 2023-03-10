#include "zzIceSkill.h"
#include "zzTime.h"
#include "zzKey.h"
#include "zzPlayer.h"

namespace zz
{
	IceSkill::IceSkill(Vector2 pos, int dir)
		: mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(32.f, 0.f))
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* IceSkill_Right = ResourceMgr::Load<Texture>(L"IceSkill_Right", L"..\\Resources\\IceKirby_Right.bmp");
		Texture* IceSkill_Left = ResourceMgr::Load<Texture>(L"IceSkill_Left", L"..\\Resources\\IceKirby_Left.bmp");

		mAni->CreateAnimation(IceSkill_Right, L"IceSkill_Right_X", Vector2(142.f, 531.f), Vector2(32.f, 32.f), Vector2(32.f, 0.f), 0.04f, 14);
		mAni->CreateAnimation(IceSkill_Left, L"IceSkill_Left_X", Vector2(423.f, 531.f), Vector2(32.f, 32.f), Vector2(-32.f, 0.f), 0.04f, 14);

		SetScale(Vector2(32.f, 32.f));


		if (dir == 1)
		{
			pos += mIntervalPos;
			mAni->PlayAnimation(L"IceSkill_Right_X", true);
		}
		else
		{
			pos -= mIntervalPos;
			mAni->PlayAnimation(L"IceSkill_Left_X", true);
		}

		SetPos(pos);
	}

	IceSkill::~IceSkill()
	{
	}

	void IceSkill::Initialize()
	{
	}

	void IceSkill::Update()
	{
		

	

		if (KEY(X, UP))
		{
			DeleteObject(this, GetLayerType());
		}
		
		

		GameObject::Update();
	}

	void IceSkill::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}

	/*void IceSkill::Release()
	{
	}*/
}