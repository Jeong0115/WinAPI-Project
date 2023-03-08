#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzGameObject.h"
#include "zzKirby.h"

namespace zz
{
	class IceKirby : public Kirby
	{
	public:
		IceKirby();
		virtual ~IceKirby();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

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
		Texture*	mTex;
		Collider*	mColli;
		Animator*	mAni;
		eIceKirby	mState;

		float		mPassedTime;
		bool		mbRun;
	};

}
