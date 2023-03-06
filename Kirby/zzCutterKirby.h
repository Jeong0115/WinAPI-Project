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

		void Enter();
		void Exit();

	public:
		enum class eCutterKirby
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

		eCutterKirby	mState;

		float			mPassedTime;
		bool			mbPressX;
	};
}

