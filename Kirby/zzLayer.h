#pragma once

#include "zzEntity.h"
#include "zzGameObject.h"

namespace zz
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	public:
		void AddGameObject(GameObject* obj);

	private:
		std::vector<GameObject*> mGameObjects;
	};
}

