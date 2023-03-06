#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzGameObject.h"
#include "zzKirby.h"

namespace zz
{
	class IceKirby : public GameObject
	{
	public:
		IceKirby(Kirby* owner);
		virtual ~IceKirby();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Enter();
		void Exit();

		enum class eIceKirby
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
		Texture*	mTex;
		Collider*	mColli;
		Animator*	mAni;
		Kirby*		mOwner;
		eIceKirby	mState;
	};

}
