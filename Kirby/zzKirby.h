#pragma once

#include "zzGameObject.h"


namespace zz
{
	class Kirby : public GameObject
	{
	public:
		Kirby();
		virtual ~Kirby();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();


		virtual void Enter();
		virtual void Exit();

		virtual void OnCollisionEnter(GameObject* other) {}
		virtual void OnCollision(GameObject* other) {}
		virtual void OnCollisionExit(GameObject* other) {}

		virtual Vector2 GetPos() override { return mPos; }
		virtual Vector2 GetScale() override { return mScale; }
		virtual void SetPos(Vector2 pos) override { mPos = pos; }
		virtual void SetScale(Vector2 scale) override { mScale = scale; }

	public:
		int GetType() { return temp; }

		static int GetDir() { return mDir; }
		static void SetDir(int dir) { mDir = dir; }

		static void KirbyInitialize(Kirby* defaultKirby);

	private:
		static eTransformType	type;
		static int temp;
		static int mDir;
		static std::vector<Kirby*> mKirbyTransforms;

		static Vector2 mPos;
		static Vector2 mScale;

		int prevTemp;
	};	
}

