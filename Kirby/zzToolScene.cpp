#include "zzToolScene.h"
#include "zzTile.h"
#include "zzSceneMgr.h"
#include "zzKey.h"

namespace zz
{
	ToolScene::ToolScene()
	{
	}

	ToolScene::~ToolScene()
	{
	}

	void ToolScene::Initialize()
	{
		Scene::Initialize();
	}

	void ToolScene::Update()
	{
		if (KEY(ENTER, UP))
		{
			SceneMgr::LoadScene(eSceneType::PLAY);
		}
		Scene::Update();
	}

	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void ToolScene::Enter()
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				Tile* tile = new Tile();
				tile->SetPos(Vector2(j * TILE_SIZE.x, i * TILE_SIZE.y));

				AddGameObject(tile, eLayerType::TILE);
			}
		}
	}

	void ToolScene::Exit()
	{
	}
}