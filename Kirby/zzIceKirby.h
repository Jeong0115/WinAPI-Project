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

	public:

	private:
		Texture* mTex;
		Collider* mColli;
		Animator* mAni;
		Kirby* mOwner;
	};

}
