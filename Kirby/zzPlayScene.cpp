#include "zzPlayScene.h"
#include "zzKirby.h"
#include "zzMonster.h"
#include "zzApplication.h"

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

		/*Monster* monster = new Monster();
		monster->SetName(L"monster");

		AddGameObject(monster, eLayerType::MONSTER);*/

		Vector2 resolution = Application::GetResolution();

		int cnt = 6;

		float term = (resolution.x - 300) / (float)(cnt - 1);

		for (int i = 0; i < cnt; i++)
		{
			Monster* monster = new Monster();
			monster->SetPos(Vector2(50.f + term * i, 500.f));
			monster->SetCenterPos(Vector2(monster->GetPos().x + 50, monster->GetPos().y));
			AddGameObject(monster, eLayerType::MONSTER);
		}

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
