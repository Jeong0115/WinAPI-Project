#include "zzPlayScene.h"

#include "zzApplication.h"
#include "zzCollisionMgr.h"
#include "zzKey.h"
#include "zzSceneMgr.h"
#include "zzCamera.h"

#include "zzDefaultKirby.h"
#include "zzTransformEffect.h"
#include "zzSkill.h"
#include "zzBK_Stage1.h"
#include "zzMonster.h"
#include "zzStage1.h"
#include "zzInventory.h"
#include "zzAbilityUI.h"
#include "zzHP.h"
#include "zzKirby.h"

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
		DefaultKirby* defaultKirby = new DefaultKirby();
		defaultKirby->SetName(L"DefaultKirby");

		AddGameObject(defaultKirby, eLayerType::PLAYER);

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
		effect->SetObj(kirby);
		AddGameObject(effect, eLayerType::EFFECT);

		/*Skill* skill = new Skill(defaultKirby);
		AddGameObject(skill, eLayerType::SKILL);*/

		Inventory* inven = new Inventory();
		AddGameObject(inven, eLayerType::INVENTORY);

		AbilityUI* abilityUI = new AbilityUI();
		AddGameObject(abilityUI, eLayerType::UI);

		HP* hp = new HP();
		AddGameObject(hp, eLayerType::UI);

		Inventory* inven = new Inventory();
		AddGameObject(inven, eLayerType::INVENTORY);

		CollisionMgr::CheckCollision(eLayerType::SKILL, eLayerType::MONSTER);
		CollisionMgr::CheckCollision(eLayerType::MONSTER, eLayerType::PLAYER);


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
	}

	void PlayScene::Enter()
	{
	}

	void PlayScene::Exit()
	{
		CollisionMgr::ResetCollision();
	}

	
}
