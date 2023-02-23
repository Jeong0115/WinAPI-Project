#include "zzScene.h"


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

	void Scene::Exit()
	{
	}

	void Scene::AddGameObject(GameObject* obj, eLayerType layer)
	{
		if (mLayers[(UINT)layer] == nullptr) //함수 호출 비용, 인라인으로 나중에 구현할 수 있으면 수정
		{
			mLayers[(UINT)layer] = new Layer;
		}

		mLayers[(UINT)layer]->AddGameObject(obj);
	}
}