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
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;

	private:
	};
}

