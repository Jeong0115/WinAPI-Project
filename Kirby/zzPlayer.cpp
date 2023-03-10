#include "zzKirby.h"
#include "zzTime.h"
#include "zzKey.h"

#include "zzSceneMgr.h"
#include "zzScene.h"

#include "zzIceKirby.h"
#include "zzFireKirby.h"
#include "zzDefaultKirby.h"
#include "zzCutterKirby.h"

#include "zzTransformEffect.h"
#include "zzStar.h"
#include "zzPlayer.h"

#include "zzFireTemp.h"

namespace zz
{
	Player::Player()
		: prevTemp(0)
		, mAni(nullptr)
		, mColli(nullptr)
		, temp(0)
		, mDefaultScale(Vector2(24.f, 24.f))
		, mKirbyState(eState::ACTIVE)
	{
		SetType(eAbillityType::DEFAULT);
	}

	Player::~Player()
	{
		for (int i = 0; i < (UINT)eAbillityType::END; i++)
		{
			delete mKirbyAbility[i];
		}
	}

	void Player::Initialize()
	{
		
		//Camera::SetLookPos(Vector2(20.f, 96.f));
		//Camera::SetLookPos(GetPos());

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		SetPos(Vector2(50.f, 145.f));
		SetScale(mDefaultScale);

		mKirbyAbility.resize((UINT)eAbillityType::END);

		mKirbyAbility[(UINT)eAbillityType::DEFAULT] = new DefaultKirby(this);
		mKirbyAbility[(UINT)eAbillityType::DEFAULT]->SetName(L"DefaultKirby");
		mKirbyAbility[(UINT)eAbillityType::FIRE] = new FireKirby(this);
		mKirbyAbility[(UINT)eAbillityType::FIRE]->SetName(L"FireKirby");
		mKirbyAbility[(UINT)eAbillityType::ICE] = new IceKirby(this);
		mKirbyAbility[(UINT)eAbillityType::ICE]->SetName(L"IceKirby");
		mKirbyAbility[(UINT)eAbillityType::CUTTER] = new CutterKirby(this);
		mKirbyAbility[(UINT)eAbillityType::CUTTER]->SetName(L"CutterKirby");

		for (UINT i = 0; i < (UINT)eAbillityType::END; i++)
		{
			mKirbyAbility[i]->Initialize();
		}

		Camera::SetTarget(this);
	}

	void Player::Update()
	{
		if (GetPos().x < 10.f)
		{
			SetPos(Vector2(10.f, GetPos().y));
		}
		if (GetPos().x >1575.f)
		{
			SetPos(Vector2(1575.f, GetPos().y));
		}

		if (prevTemp != temp)
		{
			prevTemp = temp;
		}

		mKirbyAbility[temp]->Update();

		if (KEY(Z, DOWN))
		{
			temp++;
			if (temp >= (UINT)eAbillityType::END)
				temp = 0;

			mKirbyAbility[prevTemp]->Exit();
			mKirbyAbility[temp]->Enter();

			mKirbyState = eState::ACTIVE;
			SetScale(Player::GetKirbyScale());

		}
		GameObject::Update();
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Player::OnCollisionEnter(GameObject* other)
	{
		if(GetState()==eState::ACTIVE)
		{
			if (other->GetLayerType() == eLayerType::MONSTER && !(other->GetState() == eState::INHALE))
			{
				mKirbyAbility[temp]->Exit();

				if (temp != 0)
				{
					Star* star = new Star(GetPos(), GetDir());
					CreateObject(star, eLayerType::EFFECT);
				}

				temp = (UINT)eAbillityType::DEFAULT;


				mKirbyAbility[temp]->Enter();

				dynamic_cast<DefaultKirby*>(mKirbyAbility[temp])->OnCollisionEnter();
			}

			if (other->GetLayerType() == eLayerType::MONSTER && (other->GetState() == eState::INHALE))
			{
				mKirbyAbility[temp]->Exit();
				temp = (UINT)other->GetType();
				mKirbyAbility[temp]->Enter();

				DeleteObject(other, eLayerType::MONSTER);

				FireTemp* f = new FireTemp();
				CreateObject(f, eLayerType::ITEM);
			}
		}

	}
	void Player::OnCollision(GameObject* other)
	{

	}
	void Player::OnCollisionExit(GameObject* other)
	{

	}

}