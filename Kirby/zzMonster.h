#pragma once

#include "zzGameObject.h"
#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzTexture.h"

namespace zz
{
	class Monster : public GameObject
	{
	public:
		Monster();
		virtual ~Monster();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;
		virtual void OnCollision(GameObject* other) override;
		virtual void OnCollisionExit(GameObject* other) override;
	public:
		float GetSpeed() { return mSpeed; }
		void SetSpeed(float speed) { mSpeed = speed; }
		void SetCenterPos(Vector2 pos) { mCenterPos = pos; }

	private:
		Vector2		mCenterPos;
		float		mSpeed;
		float		mMaxDistance;
		int			mDir;

		Collider*	mColli;
		Animator*	mAni;

		bool		mbHit;
		bool		mbCadaver;
		float		mHitTime;
		float		mDeadTime;

		int			mHp;
	};
}