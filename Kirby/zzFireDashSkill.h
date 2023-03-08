#pragma once

#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzGameObject.h"

namespace zz
{
	class Kirby;

	class FireDashSkill : public GameObject
	{
	public:
		FireDashSkill(Vector2 pos, int dir);
		virtual ~FireDashSkill();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Dead() { DeleteObject(this, eLayerType::SKILL); }
		void SetOwner(Kirby* owner) { mOwner = owner; }

	private:
		Animator*	mAni;
		Collider*	mColli;
		Vector2		mIntervalPos;
		float		mPassedTime;
		Kirby*		mOwner;
	};

}
