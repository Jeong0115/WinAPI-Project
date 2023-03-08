#pragma once

#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzGameObject.h"

namespace zz
{
	class FireSkill : public GameObject
	{
	public:
		FireSkill(Vector2 pos, int dir);
		virtual ~FireSkill();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;	

	private:
		Animator* mAni;
		Collider* mColli;
		Vector2 mIntervalPos;

	};

}
