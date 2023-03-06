#include "zzScene.h"
#include "zzTile.h"
#include "zzCollider.h"

namespace zz
{
	Scene::Scene()
	{
		mLayers.resize((UINT)eLayerType::END);
	}

	Scene::~Scene()
	{
		for (UINT i = 0; i < (UINT)eLayerType::END; i++)
		{
			delete mLayers[i];
		}
	}

	void Scene::Initialize()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;
			layer->Initialize();
		}
	}

	void Scene::Update()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;
			layer->Update();
		}
	}
	
	void Scene::Render(HDC hdc)
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;
			layer->Render(hdc);
		}
	}

	void Scene::Enter()
	{
	}

	void Scene::Exit()
	{
	}

	void Scene::AddGameObject(GameObject* obj, eLayerType layer)
	{
		if (mLayers[(UINT)layer] == nullptr) //함수 호출 비용, 인라인으로 나중에 구현할 수 있으면 수정
		{
			mLayers[(UINT)layer] = new Layer;
		}

		obj->SetLayerType(layer);
		mLayers[(UINT)layer]->AddGameObject(obj);
	}

	void Scene::ChangeGameObject(GameObject* prevObj, GameObject* curObj, eLayerType layer)
	{
		mLayers[(UINT)layer]->ChangeGameObject(prevObj, curObj);
	}

	void Scene::DeleteLayer(eLayerType layer)
	{
		delete mLayers[(UINT)layer];
		mLayers[(UINT)layer] = nullptr;
	}

	void Scene::CreateTile(UINT xCnt, UINT yCnt)
	{
		for (UINT i = 0; i < yCnt; i++)
		{
			for (UINT j = 0; j < xCnt; j++)
			{
				Tile* tile = new Tile();
				tile->SetPos(Vector2(j * TILE_SIZE.x, i * TILE_SIZE.y));
				tile->SetScale(Vector2(TILE_SIZE.x, TILE_SIZE.y));

				tile->AddComponent<Collider>();

				AddGameObject(tile, eLayerType::TILE);
			}
		}
	}

}