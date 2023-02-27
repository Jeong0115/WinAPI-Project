#pragma once

#include "zzGameObject.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzCollider.h"

namespace zz
{
	class FireKirbySkill : public GameObject
	{
	public:
		FireKirbySkill();
		virtual ~FireKirbySkill();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		GameObject* obj;

	private:
		Animator* mAni;
		Collider* mColli;
		int mDir;
		//Collider* temp;
	};

}
