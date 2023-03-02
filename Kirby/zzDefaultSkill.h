#pragma once

#include "zzSkill.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzGameObject.h"

namespace zz
{
	class DefaultSkill : public GameObject
	{
	public:
		DefaultSkill(Skill* owner);
		virtual ~DefaultSkill();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		//irtual void Release();



	private:
		Skill* mOwner;
		Animator* mAni;
		Collider* mColli;
		Vector2 mIntervalPos;

		int mDir;
	};
}
