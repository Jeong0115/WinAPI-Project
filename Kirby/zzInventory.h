#pragma once

#include "zzGameObject.h"
#include "zzAnimator.h"

namespace zz
{

	class Inventory : public GameObject
	{
	public:
		Inventory();
		virtual ~Inventory();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Animator* mAni;
	};

}
