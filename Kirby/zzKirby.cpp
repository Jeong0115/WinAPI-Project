#include "zzKirby.h"
#include "zzTime.h"
#include "zzKey.h"

#include "zzSceneMgr.h"
#include "zzScene.h"

#include "zzIceKirby.h"
#include "zzFireKirby.h"
#include "zzDefaultKirby.h"
#include "zzCutterKirby.h"

namespace zz
{
	eTransformType Kirby::type = eTransformType::DEFAULT;
	int Kirby::temp;
	int Kirby::mDir = 1;
	std::vector<Kirby*> Kirby::mKirbyTransforms = {};
	Vector2 Kirby::mPos = Vector2(50.f, 145.f);
	Vector2 Kirby::mScale = Vector2(24.f, 24.f);

	void Kirby::KirbyInitialize(Kirby* defaultKirby)
	{
		mKirbyTransforms.resize((UINT)eTransformType::END);

		mKirbyTransforms[(UINT)eTransformType::DEFAULT] = defaultKirby;
		mKirbyTransforms[(UINT)eTransformType::DEFAULT]->SetName(L"DefaultKirby");
		mKirbyTransforms[(UINT)eTransformType::FIRE] = new FireKirby();
		mKirbyTransforms[(UINT)eTransformType::FIRE]->SetName(L"FireKirby");
		mKirbyTransforms[(UINT)eTransformType::ICE] = new IceKirby();
		mKirbyTransforms[(UINT)eTransformType::ICE]->SetName(L"IceKirby");
		mKirbyTransforms[(UINT)eTransformType::CUTTER] = new CutterKirby();
		mKirbyTransforms[(UINT)eTransformType::CUTTER]->SetName(L"CutterKirby");

		for (UINT i = 1; i < (UINT)eTransformType::END; i++)
		{
			mKirbyTransforms[i]->Initialize();
			mKirbyTransforms[i]->SetLayerType(eLayerType::PLAYER);
		}
	}

	Kirby::Kirby()
		: prevTemp(0)
	{
	}

	Kirby::~Kirby()
	{
		/*SceneMgr::GetPlayScene()->ChangeGameObject(mKirbyTransforms[temp], nullptr, eLayerType::PLAYER);

		for (auto kirby : mKirbyTransforms)
		{
			delete kirby;
		}*/

		/*for (int i = 0; i < mKirbyTransforms.size(); i++)
		{
			delete mKirbyTransforms[i];
			mKirbyTransforms[i] = nullptr;
		}	*/
	}

	void Kirby::Initialize()
	{
		
		//Camera::SetLookPos(Vector2(20.f, 96.f));
		//Camera::SetLookPos(GetPos());
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

		
		if (KEY(Z, DOWN))
		{
			temp++;
			if (temp >= (UINT)eTransformType::END)
				temp = 0;

			mKirbyTransforms[prevTemp]->Exit();
			SceneMgr::GetCurScene()->ChangeGameObject(mKirbyTransforms[prevTemp], mKirbyTransforms[temp], eLayerType::PLAYER);
			mKirbyTransforms[temp]->Enter();

			Camera::SetTarget(mKirbyTransforms[temp]);
		}

		//mKirbyTransforms[temp]->Update();
	}

	void Kirby::Render(HDC hdc)
	{
	}

	void Kirby::Release()
	{
		/*for (auto kirby : mKirbyTransforms)
		{
			delete kirby;
			kirby = nullptr;
		}
		GameObject::Release();*/
	}

	void Kirby::Enter()
	{
	}

	void Kirby::Exit()
	{
	}

}