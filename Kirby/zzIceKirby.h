#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzKirby.h"

namespace zz
{
	class IceKirby : public Kirby
	{
	public:
		IceKirby(Kirby* owner);
		virtual ~IceKirby();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	public:

	private:
		Texture* mTex;
		Collider* mColli;
		Animator* mAni;
		Kirby* mOwner;
	};

}
