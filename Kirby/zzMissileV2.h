#pragma once

#include "zzGameObject.h"

namespace zz
{
	class MissileV2 : public GameObject
	{
	public:
		MissileV2();
		virtual ~MissileV2();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	public:
		void SetDir(bool bUp)
		{
			if (bUp)
				mDir = -1.f;
			else
				mDir = 1.f;
		}

	private:
		float mDir;
	};
}

