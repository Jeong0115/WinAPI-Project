#pragma once

#include "zzGameObject.h"


namespace zz
{
	class Collider;
	class Kirby : public GameObject
	{
	public:
		Kirby();
		virtual ~Kirby();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		static void End();


		virtual void Enter();
		virtual void Exit();

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

		virtual Vector2 GetPos() { return mKirbyPos; }
		virtual Vector2 GetScale() { return mKirbyScale; }
		virtual void SetPos(Vector2 pos) { mKirbyPos = pos; }
		virtual void SetScale(Vector2 scale) { mKirbyScale = scale; }
		virtual void SetDir(int dir) { mKirbyDir = dir; }
		virtual int GetDir() { return mKirbyDir; }
		

		virtual eState GetState() { return mKirbyState; }
		virtual void SetState(eState state) { mKirbyState = state; } // 수정예정

		static inline Vector2 GetKirbyScale() { return mDefaultScale; }


	public:
		static int GetType() { return temp; }

		static void KirbyInitialize(Kirby* defaultKirby);

	private:
		static eTransformType	type;
		static int temp;
		static int mKirbyDir;
		static std::vector<Kirby*> mKirbyAbility;

		static Vector2 mKirbyPos;
		static Vector2 mKirbyScale;
		static Vector2 mDefaultScale;

		static eState mKirbyState;

		int prevTemp;

	protected:
		static Collider* mKirbyColli;
	};	
}

