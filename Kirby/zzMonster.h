#pragma once

#include "zzGameObject.h"
namespace zz
{
	class Monster : public GameObject
	{
	public:
		Monster();
		virtual ~Monster();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	public:
		float GetSpeed() { return mSpeed; }
		void SetSpeed(float speed) { mSpeed = speed; }
		void SetCenterPos(Vector2 pos) { mCenterPos = pos; }

	private:
		Vector2		mCenterPos;
		float		mSpeed;
		float		mMaxDistance;
		int			mDir;
	};
}