#pragma once

#include "zzEntity.h"
#include "zzLayer.h"

namespace zz
{
	class Scene : public Entity 
	{
	public:
		Scene();
		virtual ~Scene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	public:
		void AddGameObject(GameObject* obj, eLayerType layer);

	private:
		std::vector<Layer*> mLayers;
	};
}

