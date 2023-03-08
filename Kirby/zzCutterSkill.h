#pragma once

#include "zzSkill.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzGameObject.h"
#include "zzKirby.h"

namespace zz
{
	class CutterSkill : public GameObject
	{
	public:
		CutterSkill(Vector2 pos, int dir);
		virtual ~CutterSkill();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		//virtual void Release();


	private:
		Animator*		mAni;
		Collider*		mColli;
		Vector2			mIntervalPos;

		bool			mbPressX;
		float			mPassedTime;
	};

}
