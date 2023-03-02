#include "zzIceSkill.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	IceSkill::IceSkill(Skill* owner)
		: mOwner(owner)
		, mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(32.f, 0.f))
		, mDir(1)
	{
	}

	IceSkill::~IceSkill()
	{
	}

	void IceSkill::Initialize()
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* IceSkill_Right = ResourceMgr::Load<Texture>(L"IceSkill_Right", L"..\\Resources\\IceKirby_Right.bmp");
		Texture* IceSkill_Left = ResourceMgr::Load<Texture>(L"IceSkill_Left", L"..\\Resources\\IceKirby_Left.bmp");

		mAni->CreateAnimation(IceSkill_Right, L"IceSkill_Right_X", Vector2(142.f, 531.f), Vector2(32.f, 32.f), Vector2(32.f, 0.f), 0.04f, 14);
		mAni->CreateAnimation(IceSkill_Left, L"IceSkill_Left_X", Vector2(423.f, 531.f), Vector2(32.f, 32.f), Vector2(-32.f, 0.f), 0.04f, 14);

		SetPos(Vector2(-20.f, -20.f));
		SetScale(Vector2(32.f, 32.f));


		GameObject::Initialize();
		//temp = new Collider;
		//SetComponent<Collider>(temp);
	}

	void IceSkill::Update()
	{
		Vector2 vPos = GetPos();

		if (KEY(X, PRESSED))
		{
			vPos = mOwner->GetPos();
			mDir = mOwner->GetDir();

			if (mDir == 1)
			{
				vPos += mIntervalPos;
				mAni->PlayAnimation(L"IceSkill_Right_X", false);
			}
			else
			{
				vPos -= mIntervalPos;
				mAni->PlayAnimation(L"IceSkill_Left_X", false);
			}
		}

		if (KEY(X, UP))
		{
			/*mAni->StopAnimation(L"FireSkill1");
			mAni->StopAnimation(L"FireSkill");*/
			vPos = Vector2(-20.f, -20.f);
		}
		
		SetPos(vPos);

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