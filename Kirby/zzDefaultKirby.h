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
			END
		};
		
	private:
		void idle(int dir);
		void walk(int dir);
		void run(int dir);
		void skill(int dir);
		void down(int dir);

		void jump();
	private:
		Collider*		mColli;
		Animator*		mAni;

		eDefaultKirby	mState;

		float			mPassedTime;
		bool			mbPressX;

		bool			mbRun;

		int a = 0;
	};
}

