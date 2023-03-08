#pragma once

#include "zzGameObject.h"

namespace zz
{
	class HP : public GameObject
	{
	public:
		HP();
		virtual ~HP();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Texture* mTex;
	};
}


