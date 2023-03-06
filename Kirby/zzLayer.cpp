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
			/*if (mGameObjects.size() >= 2)
				mGameObjects[1] = nullptr;*/

			if (mGameObjects[i] == nullptr)
				continue;
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
		std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		for (; iter != mGameObjects.end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = mGameObjects.erase(iter);
			}
			else
			{
				(*iter)->Render(hdc);
				iter++;
			}
		}


	}

	void Layer::Release()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;
			obj->Release();
		}
		
		
	}

	void Layer::AddGameObject(GameObject* obj)
	{
		if (obj == nullptr)
			return;

		mGameObjects.push_back(obj);
	}

	void Layer::ChangeGameObject(GameObject* prevObj, GameObject* curObj)
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i] == prevObj)
			{
				mGameObjects[i] = curObj;
				break;
			}
		}
	}
}