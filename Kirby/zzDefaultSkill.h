#pragma once

#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzGameObject.h"

namespace zz
{
	class DefaultSkill : public GameObject
	{
	public:
		DefaultSkill(Vector2 pos, int dir);
		virtual ~DefaultSkill();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		//irtual void Release();



	private:
		Animator* mAni;
		Collider* mColli;
		Vector2 mIntervalPos;
	};
}
