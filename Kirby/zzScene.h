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
		virtual void Enter();
		virtual void Exit();

	public:
		void AddGameObject(GameObject* obj, eLayerType layer);
		void ChangeGameObject(GameObject* prevObj, GameObject* curObj, eLayerType layer);
		void DeleteLayer(eLayerType layer);
		Layer* GetLayer(eLayerType type) { return mLayers[(UINT)type]; }

		void CreateTile(UINT xCnt, UINT yCnt);

	private:
		std::vector<Layer*> mLayers;
	};
}

