#include "zzPlayScene.h"
#include "zzKirby.h"
#include "zzMonster.h"
#include "zzApplication.h"
#include "zzBackGround.h"
#include "zzCollisionMgr.h"
#include "zzKey.h"
#include "zzSceneMgr.h"
#include "zzTransformEffect.h"
#include "zzSkill.h"

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

		BackGround* bk = new BackGround();
		bk->SetName(L"stage1");

		AddGameObject(bk, eLayerType::BACKGROUND);

		Monster* monster = new Monster();
		monster->SetName(L"monster");

		AddGameObject(monster, eLayerType::MONSTER);

		TransformEffect* effect = new TransformEffect();
		effect->obj = kirby;
		AddGameObject(effect, eLayerType::EFFECT);

		Skill* skill = new Skill();
		skill->kirby = kirby;
		AddGameObject(skill, eLayerType::SKILL);

		CollisionMgr::CheckCollision(eLayerType::SKILL, eLayerType::MONSTER);
		CollisionMgr::CheckCollision(eLayerType::MONSTER, eLayerType::PLAYER);

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
