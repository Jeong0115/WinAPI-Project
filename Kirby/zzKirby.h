#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Kirby : public GameObject
	{
	public:
		Kirby();
		virtual ~Kirby();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	public:
		void CreateMissile();
		void CreateMissileV2();

	private:
		bool bMissileType;
	};
}

