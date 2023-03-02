#pragma once

#include "zzSkill.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzGameObject.h"

namespace zz
{
	class FireSkill : public GameObject
	{
	public:
		FireSkill(Skill* owner);
		virtual ~FireSkill();

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
		//Collider* temp;
	};

}
