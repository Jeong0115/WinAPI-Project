#pragma once

#include "zzGameObject.h"
#include "zzAnimator.h"

namespace zz
{

	class AbilityUI : public GameObject
	{
	public:
		AbilityUI();
		virtual ~AbilityUI();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Texture* mTex;
		int mType;
	};

}
