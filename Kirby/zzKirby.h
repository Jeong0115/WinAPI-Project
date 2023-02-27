#pragma once

#include "zzGameObject.h"
#include "zzTransform.h"
#include "zzCollider.h"
#include "zzkirbyComponent.h"
#include "zzAnimator.h"

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

	public:
		
	private:
		Texture* mTex;
		Transform* mTr;
		Collider* mColli;
		Animator* mAni;

		std::vector<std::wstring> mStayRightKeys;
		std::vector<std::wstring> mStayLeftKeys;
		std::vector<std::wstring> mWalkRightKeys;
		std::vector<std::wstring> mWalkLeftKeys;

		int state;

	};
}

