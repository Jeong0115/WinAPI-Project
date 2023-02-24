#pragma once

#include "zzGameObject.h"
#include "zzTransform.h"
#include "zzCollider.h"
#include "zzkirbyComponent.h"
#include "zzAnimator.h"

namespace zz
{
	class Kirby : public GameObject
	{
	public:
		Kirby();
		virtual ~Kirby();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	public:
		
	private:
		Texture* mTex;
		Transform* mTr;
		Collider* mColli;
		Animator* mAni;
		
	};
}

