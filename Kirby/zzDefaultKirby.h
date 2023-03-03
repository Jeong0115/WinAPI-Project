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
		enum class eDefaultKirby
		{
			IDLE,
			MOVE,
			SKILL,
			DOWN,
			END
		};
		
	private:
		void idle(int dir);
		void move(int dir);
		void skill(int dir);
		void down(int dir);

	private:
		Collider*		mColli;
		Animator*		mAni;
		Kirby*			mOwner;

		eDefaultKirby	mState;

		float			mPassedTime;
	};
}

