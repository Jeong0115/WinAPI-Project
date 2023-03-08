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

namespace zz
{
	eTransformType Kirby::type = eTransformType::DEFAULT;
	int Kirby::temp;
	int Kirby::mKirbyDir = 1;
	std::vector<Kirby*> Kirby::mKirbyAbility = {};
	Vector2 Kirby::mKirbyPos = Vector2(50.f, 145.f);
	Vector2 Kirby::mKirbyScale = Vector2(24.f, 24.f);
	Vector2 Kirby::mDefaultScale = Vector2(24.f, 24.f);
	eState Kirby::mKirbyState = eState::ACTIVE;

	Collider* Kirby::mKirbyColli = nullptr;

	void Kirby::KirbyInitialize(Kirby* defaultKirby)
	{
		
		mKirbyAbility.resize((UINT)eTransformType::END);

		mKirbyAbility[(UINT)eTransformType::DEFAULT] = defaultKirby;
		mKirbyAbility[(UINT)eTransformType::DEFAULT]->SetName(L"DefaultKirby");
		mKirbyAbility[(UINT)eTransformType::FIRE] = new FireKirby();
		mKirbyAbility[(UINT)eTransformType::FIRE]->SetName(L"FireKirby");
		mKirbyAbility[(UINT)eTransformType::ICE] = new IceKirby();
		mKirbyAbility[(UINT)eTransformType::ICE]->SetName(L"IceKirby");
		mKirbyAbility[(UINT)eTransformType::CUTTER] = new CutterKirby();
		mKirbyAbility[(UINT)eTransformType::CUTTER]->SetName(L"CutterKirby");

		for (UINT i = 1; i < (UINT)eTransformType::END; i++)
		{
			mKirbyAbility[i]->Initialize();
			mKirbyAbility[i]->SetLayerType(eLayerType::PLAYER);
		}
	}

	Kirby::Kirby()
		: GameObject()
		, prevTemp(0)
	{
	}

	Kirby::~Kirby()
	{
	}

	void Kirby::Initialize()
	{
		
		//Camera::SetLookPos(Vector2(20.f, 96.f));
		//Camera::SetLookPos(GetPos());

		mKirbyAbility.resize((UINT)eTransformType::END);

		mKirbyAbility[(UINT)eTransformType::DEFAULT] = new DefaultKirby();
		mKirbyAbility[(UINT)eTransformType::DEFAULT]->SetName(L"DefaultKirby");
		mKirbyAbility[(UINT)eTransformType::FIRE] = new FireKirby();
		mKirbyAbility[(UINT)eTransformType::FIRE]->SetName(L"FireKirby");
		mKirbyAbility[(UINT)eTransformType::ICE] = new IceKirby();
		mKirbyAbility[(UINT)eTransformType::ICE]->SetName(L"IceKirby");
		mKirbyAbility[(UINT)eTransformType::CUTTER] = new CutterKirby();
		mKirbyAbility[(UINT)eTransformType::CUTTER]->SetName(L"CutterKirby");

		for (UINT i = 0; i < (UINT)eTransformType::END; i++)
		{
			mKirbyAbility[i]->Initialize();
			mKirbyAbility[i]->SetLayerType(eLayerType::PLAYER);
		}

		mKirbyColli = AddComponent<Collider>();
		Camera::SetTarget(this);
	}

	void Kirby::Update()
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
			if (temp >= (UINT)eTransformType::END)
				temp = 0;

			mKirbyAbility[prevTemp]->Exit();

			//TransformEffect::SetObj(mKirbyAbility[temp]);


			//SceneMgr::GetCurScene()->ChangeGameObject(mKirbyAbility[prevTemp], mKirbyAbility[temp], eLayerType::PLAYER);
			//Camera::SetTarget(mKirbyAbility[temp]);
			mKirbyAbility[temp]->Enter();
			mKirbyState = eState::ACTIVE;
			mKirbyAbility[temp]->SetScale(Kirby::GetKirbyScale());
		}
		GameObject::Update();
	}

	void Kirby::Render(HDC hdc)
	{
		mKirbyAbility[temp]->Render(hdc);
		GameObject::Render(hdc);
	}

	void Kirby::End()
	{
		for (int i = 0; i < mKirbyAbility.size(); i++)
		{

			mKirbyAbility[i]->Release();
			delete mKirbyAbility[i];
			mKirbyAbility[i] = nullptr;
		}
		//delete mKirbyColli;
	}

	void Kirby::Enter()
	{
	}

	void Kirby::Exit()
	{
	}


	void Kirby::OnCollisionEnter(GameObject* other)
	{
		if(other->GetLayerType() == eLayerType::MONSTER)
		{
			mKirbyAbility[temp]->Exit();

			if (temp != 0)
			{
				Star* star = new Star(GetPos(), GetDir());
				CreateObject(star, eLayerType::EFFECT);
			}

			temp = (UINT)eTransformType::DEFAULT;
			

			mKirbyAbility[temp]->Enter();
			mKirbyAbility[temp]->Enter();
			mKirbyAbility[temp]->OnCollisionEnter(other);
		}

	}
	void Kirby::OnCollision(GameObject* other)
	{

	}
	void Kirby::OnCollisionExit(GameObject* other)
	{

	}

}