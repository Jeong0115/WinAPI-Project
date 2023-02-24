#include "zzPlayScene.h"
#include "zzKirby.h"
#include "zzMonster.h"
#include "zzApplication.h"
#include "zzBackGround.h"
#include "zzCollisionMgr.h"
#include "zzKey.h"
#include "zzSceneMgr.h"
#include "zzFireKirbySkill.h"

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

		FireKirbySkill* fireSkill = new FireKirbySkill();
		AddGameObject(fireSkill, eLayerType::EFFECT);


		CollisionMgr::CheckCollision(eLayerType::PLAYER, eLayerType::MONSTER);
		CollisionMgr::CheckCollision(eLayerType::EFFECT, eLayerType::MONSTER);

		mTex = ResourceMgr::Load<Texture>(L"Controll", L"..\\Resources\\Controll.bmp");

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		if (KEY(P, UP))
		{
			SceneMgr::LoadScene(eSceneType::PAUSE);
		}

		Scene::Update();
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		BitBlt(hdc, 250 , 250, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc(), 0, 0, SRCCOPY);
	}

	void PlayScene::Exit()
	{
		CollisionMgr::ResetCollision();
	}

	
}
