#include "zzPlayScene.h"
#include "zzKirby.h"

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

		AddGameObject(kirby, eLayerType::PLAYER);

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

}
