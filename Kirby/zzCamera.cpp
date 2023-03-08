#include "zzCamera.h"
#include "zzApplication.h"
#include "zzKey.h"
#include "zzTime.h"

namespace zz
{
	Vector2 Camera::mLookPos = {};
	Vector2 Camera::mDiffPos = {};
	Vector2 Camera::mResoultion = {};
	Vector2 Camera::mCenterPos = {};
	//Vector2 Camera::mPrevLookPos = {};
	//Vector2 Camera::mCurLookPos = {0.f , 0.f};
	//
	//float Camera::time = 0.f;
	//float Camera::dis = 0.f;
	
	GameObject* Camera::mTarget = nullptr;


	Camera::Camera()
	{
	}

	Camera::~Camera()
	{

	}

	void Camera::Initialize()
	{
		mResoultion = Application::GetResolution();
		mCenterPos = Vector2(128.f, 145.f);
	}

	void Camera::Update()
	{
		if (mTarget)
		{
			if (mTarget->IsDead())
			{
				mTarget = nullptr;
			}

			else
			{
				mLookPos = mTarget->GetPos();
			}
		}
		CalDiff();
	}

	void Camera::CalDiff()
	{
		/*time += (float)Time::DeltaTime();

		if (time >= 1.f)
		{
			mCurLookPos = mLookPos;
		}
		else
		{
			Vector2 dir = mLookPos - mPrevLookPos;
			mCurLookPos = mPrevLookPos + dir.Normalize() * dis * (float)Time::DeltaTime();
		}*/

		

		if (mLookPos.x > 1460.f)
		{
			mLookPos.x -= mLookPos.x - 1460.f;
		}
		else if (mLookPos.x < 128.f)
		{
			mLookPos.x += 128.f - mLookPos.x;
		}

		//mDiffPos = mCurLookPos - centerPos;
		//mPrevLookPos = mCurLookPos;

		mDiffPos = mLookPos - mCenterPos;
		
	}

	

}