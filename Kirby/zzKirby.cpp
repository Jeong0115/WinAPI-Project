#include "zzKirby.h"
#include "zzTime.h"
#include "zzKey.h"

#include "zzSceneMgr.h"
#include "zzScene.h"

#include "zzIceKirby.h"
#include "zzFireKirby.h"
#include "zzDefaultKirby.h"

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

		SetPos(Vector2(15, 150));
		SetScale(Vector2(20, 18));

		for (UINT i = 0; i < (UINT)eTransformType::END; i++)
		{
			mKirbyTransforms[i]->Initialize();
		}

		
	}

	void Kirby::Update()
	{

		if (prevTemp != temp)
		{
			SetPos(mKirbyTransforms[prevTemp]->GetPos());
			mKirbyTransforms[temp]->SetPos(GetPos());

			prevTemp = temp;
		}


		mKirbyTransforms[temp]->Update();


		if (KEY(Z, DOWN))
		{
			temp++;
			if (temp >= (UINT)eTransformType::END)
				temp = 0;
			//mAni->PlayAnimation(L"TransformEffect", true);
		}


	}

	void Kirby::Render(HDC hdc)
	{
		mKirbyTransforms[temp]->Render(hdc);


	}

	void Kirby::Release()
	{
		for (auto kirby : mKirbyTransforms)
		{
			delete kirby;
		}
		GameObject::Release();
	}

}