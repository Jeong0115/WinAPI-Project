#include "zzPlayScene.h"

#include "zzApplication.h"

#include "zzKirby.h"
#include "zzMonster.h"

#include "zzStage1.h"
#include "zzCollisionMgr.h"
#include "zzKey.h"
#include "zzSceneMgr.h"
#include "zzTransformEffect.h"
#include "zzSkill.h"
#include "zzCamera.h"
#include "zzBK_Stage1.h"
#include "zzTexture.h"

namespace zz
{
	PlayScene::PlayScene()
		: mTex(nullptr)
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		Kirby* kirby = new Kirby();
		kirby->SetName(L"Kirby");

		AddGameObject(kirby, eLayerType::PLAYER);

		Stage1* stage1 = new Stage1();
		stage1->SetName(L"stage1");

		AddGameObject(stage1, eLayerType::STAGE);

		BK_Stage1* bk = new BK_Stage1();
		bk->SetName(L"BK_Stage1");

		AddGameObject(bk, eLayerType::BACKGROUND);

		Monster* monster = new Monster();
		monster->SetName(L"monster");

		AddGameObject(monster, eLayerType::MONSTER);

		TransformEffect* effect = new TransformEffect();
		effect->obj = kirby;
		AddGameObject(effect, eLayerType::EFFECT);

		Skill* skill = new Skill(kirby);
		AddGameObject(skill, eLayerType::SKILL);

		CollisionMgr::CheckCollision(eLayerType::SKILL, eLayerType::MONSTER);
		CollisionMgr::CheckCollision(eLayerType::MONSTER, eLayerType::PLAYER);

		mTex = ResourceMgr::Load<Texture>(L"Inventory", L"..\\Resources\\Inventory.bmp");

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		if (KEY(P, UP))
		{
			SceneMgr::LoadScene(eSceneType::PAUSE);
		}

		/*if (KEY(LBTN, DOWN))
		{
			Camera::SetLookPos(Camera::GetRealPos(Key::GetMousePos()));
		}*/
		Scene::Update();
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		BitBlt(hdc, 0 , 193, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc(), 0, 0, SRCCOPY);
	}

	void PlayScene::Enter()
	{
	}

	void PlayScene::Exit()
	{
		CollisionMgr::ResetCollision();
	}

	
}
