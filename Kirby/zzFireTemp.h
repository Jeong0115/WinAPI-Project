#pragma once

#include "zzGameObject.h"
#include "zzAnimator.h"

namespace zz
{

	class FireTemp : public GameObject
	{
	public:
		FireTemp();
		virtual ~FireTemp();

		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		Animator* mAni;
		float mPassedTime;
	};

}
