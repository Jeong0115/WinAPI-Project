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
	Kirby::Kirby()
		: type(eTransformType::DEFAULT)
		, mDir(1)
		, temp(0)
		, prevTemp(0)
	{
	}

	Kirby::~Kirby()
	{
		SceneMgr::GetPlayScene()->ChangeGameObject(mKirbyTransforms[temp], nullptr, eLayerType::PLAYER);

		for (auto kirby : mKirbyTransforms)
		{
			delete kirby;
		}

		/*for (int i = 0; i < mKirbyTransforms.size(); i++)
		{
			delete mKirbyTransforms[i];
			mKirbyTransforms[i] = nullptr;
		}	*/
	}

	void Kirby::Initialize()
	{
		mKirbyTransforms.resize((UINT)eTransformType::END);

		mKirbyTransforms[(UINT)eTransformType::DEFAULT] = new DefaultKirby(this);
		mKirbyTransforms[(UINT)eTransformType::DEFAULT]->SetName(L"DefaultKirby");
		mKirbyTransforms[(UINT)eTransformType::FIRE] = new FireKirby(this);
		mKirbyTransforms[(UINT)eTransformType::FIRE]->SetName(L"FireKirby");
		mKirbyTransforms[(UINT)eTransformType::ICE] = new IceKirby(this);
		mKirbyTransforms[(UINT)eTransformType::ICE]->SetName(L"IceKirby");
		mKirbyTransforms[(UINT)eTransformType::CUTTER] = new CutterKirby(this);
		mKirbyTransforms[(UINT)eTransformType::CUTTER]->SetName(L"CutterKirby");

		SetPos(Vector2(15, 150));
		SetScale(Vector2(24, 24));

		for (UINT i = 0; i < (UINT)eTransformType::END; i++)
		{
			mKirbyTransforms[i]->Initialize();
		}

		SceneMgr::GetPlayScene()->AddGameObject(mKirbyTransforms[temp], eLayerType::PLAYER);
	}

	void Kirby::Update()
	{

		if (prevTemp != temp)
		{
			SetPos(mKirbyTransforms[prevTemp]->GetPos());
			mKirbyTransforms[temp]->SetPos(GetPos());

			prevTemp = temp;
		}


		

		if (KEY(Z, DOWN))
		{
			temp++;
			if (temp >= (UINT)eTransformType::END)
				temp = 0;
			SceneMgr::GetCurScene()->ChangeGameObject(mKirbyTransforms[prevTemp], mKirbyTransforms[temp], eLayerType::PLAYER);
		}

		//mKirbyTransforms[temp]->Update();
	}

	void Kirby::Render(HDC hdc)
	{
		//mKirbyTransforms[temp]->Render(hdc);


	}

	void Kirby::Release()
	{
		for (auto kirby : mKirbyTransforms)
		{
			delete kirby;
			kirby = nullptr;
		}
		GameObject::Release();
	}

}