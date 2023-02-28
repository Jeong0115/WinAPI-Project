#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzKirby.h"

namespace zz
{
	class FireKirby : public Kirby
	{
	public:
		FireKirby(Kirby* owner);
		virtual ~FireKirby();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	public:

	private:
		Texture*	mTex;
		Collider*	mColli;
		Animator*	mAni;
		Kirby* mOwner;

	};

}
