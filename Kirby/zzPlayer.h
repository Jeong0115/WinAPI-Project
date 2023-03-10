#pragma once

#include "zzGameObject.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzKirby.h"

namespace zz
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

		eState GetState() { return mKirbyState; }
		void SetState(eState state) { mKirbyState = state; } // 수정예정

		Vector2 GetKirbyScale() { return mDefaultScale; }

		Animator* GetAni() { return mAni; }


	public:
		int GetType() { return temp; }

	private:
		int temp;

		std::vector<Kirby*> mKirbyAbility;

		Vector2 mDefaultScale;

		eState mKirbyState;

		int prevTemp;

	private:
		Collider* mColli;
		Animator* mAni;
	};	
}

