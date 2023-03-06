#include "zzGameObject.h"

namespace zz
{
	GameObject::GameObject()
		: mbDead(true)
		, mLayerType(eLayerType::END)
		, mPos(Vector2(0.f, 0.f))
	{
		mComponents.resize((UINT)eCompType::END);
	}

	GameObject::~GameObject()
	{
		for (UINT i = 0; i < (UINT)eCompType::END; i++)
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
		Vector2 renderPos = Camera::GetRenderPos(mPos);
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Render(hdc);
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
