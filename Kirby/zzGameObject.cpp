#include "zzGameObject.h"

namespace zz
{
	GameObject::GameObject()
	{
	}

	GameObject::~GameObject()
	{
		for (UINT i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] == nullptr)
				continue;
			delete mComponents[i];
		}
	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Render(hdc, mPos);
		}
	}

	void GameObject::Release()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Release();
		}
	}
}
