#pragma once

#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzGameObject.h"

namespace zz
{
	class Player;
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

		void SetOwner(Player* owner) { mOwner = owner; }
		Player* GetOwner() { return mOwner; }

	private:
		Animator* mAni;
		Collider* mColli;
		Player* mOwner;
		Vector2 mIntervalPos;
	};
}
