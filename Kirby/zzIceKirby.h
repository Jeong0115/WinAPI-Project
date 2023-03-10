#pragma once

#include "zzAnimator.h"
#include "zzKirby.h"

namespace zz
{
	class IceKirby : public Kirby
	{
	public:
		IceKirby(Player* owner);
		virtual ~IceKirby();

	public:
		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Enter();
		virtual void Exit();

		enum class eIceKirby
		{
			IDLE,
			WALK,
			RUN,
			SKILL,
			DOWN,
			END
		};

	private:
		void idle(int dir);
		void walk(int dir);
		void run(int dir);
		void skill(int dir);
		void down(int dir);

	private:
		Animator*	mAni;
		eIceKirby	mState;

		float		mPassedTime;
		bool		mbRun;
	};

}
