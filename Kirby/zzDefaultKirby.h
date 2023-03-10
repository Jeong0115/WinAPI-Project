#pragma once


#include "zzKirby.h"
#include "zzPlayer.h"
#include "zzAnimator.h"

namespace zz
{
	class DefaultKirby : public Kirby
	{
	public:
		DefaultKirby(Player* owner);
		virtual ~DefaultKirby();

	public:
		virtual void Initialize();
		virtual void Update();

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
			INHALE,
			END
		};
		
		void OnCollisionEnter();

	private:
		void idle(int dir);
		void walk(int dir);
		void run(int dir);
		void skill(int dir);
		void down(int dir);
		void damage(int dir);
		void inhale(int dir);

		void active();

		


	private:
		eDefaultKirby	mState;
		Animator*		mAni;
		float			mPassedTime;
		float			mInvincibleTime;
		bool			mbPressX;

		bool			mbRun;
	};
}

