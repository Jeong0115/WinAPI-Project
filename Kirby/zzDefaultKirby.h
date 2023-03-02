#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzGameObject.h"
#include "zzKirby.h"

namespace zz
{
	class DefaultKirby : public GameObject
	{
	public:
		DefaultKirby(Kirby* owner);
		virtual ~DefaultKirby();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	public:

	private:
		Collider* mColli;
		Animator* mAni;
		Kirby* mOwner;

		float mPassedTime;
	};
}

