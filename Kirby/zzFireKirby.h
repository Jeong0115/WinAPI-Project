#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzGameObject.h"
#include "zzKirby.h"

namespace zz
{
	class FireKirby : public GameObject
	{
	public:
		FireKirby(Kirby* owner);
		virtual ~FireKirby();

	public:
		virtual void Initialize() override;
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
