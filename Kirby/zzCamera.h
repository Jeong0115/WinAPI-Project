#pragma once

#include "zzEngine.h"
#include "zzGameObject.h"

namespace zz
{
	class Camera
	{
	public:
		Camera();
		~Camera();

	public:
		static void Update();
		static void CalDiff();

	public:
		static void SetLookPos(Vector2 pos) {
			mLookPos = pos; 
			//dis = (mLookPos - mPrevLookPos).Length() / 2.f;
			//time = 0.f;
		}
		static void SetTarget(GameObject* obj) { mTarget = obj; }
		static Vector2 GetRenderPos(Vector2 pos) { return pos - mDiffPos; }
		static Vector2 GetRealPos(Vector2 pos) { return pos + mDiffPos; } 

	private:
		static Vector2 mLookPos;
		//static Vector2 mPrevLookPos;
		//static Vector2 mCurLookPos;

		static Vector2 mDiffPos;
		static GameObject* mTarget;

		//static float time;
		//static float dis;
	};

}
