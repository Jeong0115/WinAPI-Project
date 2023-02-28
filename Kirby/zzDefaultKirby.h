#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzKirby.h"

namespace zz
{
	class DefaultKirby : public Kirby
	{
	public:
		DefaultKirby(Kirby* owner);
		virtual ~DefaultKirby();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	public:

	private:
		Collider* mColli;
		Animator* mAni;
		Kirby* mOwner;

		
	};
}

