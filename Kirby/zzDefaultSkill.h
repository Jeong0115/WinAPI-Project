#pragma once

#include "zzSkill.h"
#include "zzAnimator.h"
#include "zzCollider.h"

namespace zz
{
	class DefaultSkill : public Skill
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
