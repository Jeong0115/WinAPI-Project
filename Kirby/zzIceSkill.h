#pragma once

#include "zzSkill.h"
#include "zzAnimator.h"
#include "zzCollider.h"

namespace zz
{
	class IceSkill : public Skill
	{
	public:
		IceSkill(Skill* owner);
		virtual ~IceSkill();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		//virtual void Release();



	private:
		Skill* mOwner;
		Animator* mAni;
		Collider* mColli;
		Vector2 mIntervalPos;

		int mDir;
	};

}