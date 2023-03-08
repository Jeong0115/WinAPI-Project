#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzGameObject.h"
#include "zzKirby.h"

namespace zz
{
	class FireKirby : public Kirby
	{
	public:
		FireKirby();
		virtual ~FireKirby();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

		enum class eFireKirby
		{
			IDLE,
			WALK,
			RUN,
			SKILL,
			DASHSKILL,
			DOWN,
			END
		};

	private:
		void idle(int dir);
		void walk(int dir);
		void run(int dir);
		void skill(int dir);
		void dashSkill(int dir);
		void down(int dir);

	private:
		Animator*	mAni;
		eFireKirby	mState;

		float		mPassedTime;
		bool		mbRun;
	};

}
