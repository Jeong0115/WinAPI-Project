#include "zzPlayScene.h"
#include "zzKirby.h"
#include "zzMonster.h"
#include "zzApplication.h"
#include "zzBackGround.h"
#include "zzCollisionMgr.h"

namespace zz
{
	PlayScene::PlayScene()
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		Kirby* kirby = new Kirby();
		kirby->SetName(L"kirby");

		AddGameObject(kirby, eLayerType::PLAYER);

		BackGround* bk = new BackGround();
		bk->SetName(L"stage1");

		AddGameObject(bk, eLayerType::BACKGROUND);

		Monster* monster = new Monster();
		monster->SetName(L"monster");

		AddGameObject(monster, eLayerType::MONSTER);

		CollisionMgr::CheckCollision(eLayerType::PLAYER, eLayerType::MONSTER);

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PlayScene::Exit()
	{
		CollisionMgr::ResetCollision();
	}

	
}
