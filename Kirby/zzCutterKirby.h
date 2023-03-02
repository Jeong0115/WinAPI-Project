#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzGameObject.h"
#include "zzKirby.h"

namespace zz
{
	class CutterKirby : public GameObject
	{
	public:
		CutterKirby(Kirby* owner);
		virtual ~CutterKirby();

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

		bool mbPressX;
	};
}

