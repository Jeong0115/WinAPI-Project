#pragma once

#include "zzSkill.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzGameObject.h"

namespace zz
{
	class CutterSkill : public GameObject
	{
	public:
		CutterSkill(Skill* owner);
		virtual ~CutterSkill();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		//virtual void Release();



	private:
		Skill*			mOwner;
		Animator*		mAni;
		Collider*		mColli;
		Vector2			mIntervalPos;

		bool			mbPressX;
		float			mPassedTime;
		bool			x = false;

		int				mDir;
	};

}
