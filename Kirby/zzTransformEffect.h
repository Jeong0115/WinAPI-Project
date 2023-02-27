#pragma once

#include "zzGameObject.h"
#include "zzAnimator.h"

namespace zz
{
	class TransformEffect : public GameObject
	{
	public:
		TransformEffect();
		virtual ~TransformEffect();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		GameObject* obj;

	private:
		Animator* mAni;
	};

}
