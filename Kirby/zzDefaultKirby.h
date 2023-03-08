#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzGameObject.h"
#include "zzKirby.h"

namespace zz
{
	class DefaultKirby : public Kirby
	{
	public:
		DefaultKirby();
		virtual ~DefaultKirby();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

	public:
		enum class eDefaultKirby
		{
			IDLE,
			WALK,
			RUN,
			SKILL,
			DOWN,
			DAMAGE,
			END
		};
		
	private:
		void idle(int dir);
		void walk(int dir);
		void run(int dir);
		void skill(int dir);
		void down(int dir);
		void damage(int dir);

		void active();

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

	private:
		Animator*		mAni;

		eDefaultKirby	mState;

		float			mPassedTime;
		float			mInvincibleTime;
		bool			mbPressX;

		bool			mbRun;

		int a = 0;
	};
}

