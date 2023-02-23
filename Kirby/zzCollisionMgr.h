#pragma once

#include "zzEngine.h"
#include "zzCollider.h"

namespace zz
{
	class CollisionMgr
	{
	public:
		CollisionMgr();
		~CollisionMgr();

	public:
		static void Initialize();
		static void Update();
		static void Update2(eLayerType left, eLayerType right);
		static void CheckCollision(eLayerType left, eLayerType right);
		static void ResetCollision();
		static bool IsCollision(Collider* left, Collider* right);

	private:
		static UINT mCheck[(UINT)eLayerType::END];

	};
}

