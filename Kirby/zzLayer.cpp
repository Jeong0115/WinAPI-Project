#include "zzLayer.h"


namespace zz
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (UINT i = 0; i < mGameObjects.size(); i++)
		{
			delete mGameObjects[i];
		}
	}

	void Layer::Initialize()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;
			obj->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;
			obj->Update();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;
			obj->Render(hdc);
		}
	}

	void Layer::Release()
	{
	}

	void Layer::AddGameObject(GameObject* obj)
	{
		if (obj == nullptr)
			return;

		mGameObjects.push_back(obj);
	}
}