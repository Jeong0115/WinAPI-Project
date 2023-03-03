#pragma once

#include "zzComponent.h"
#include "zzAnimation.h"

namespace zz
{
	class Animator : public Component
	{
	public:
		Animator();
		virtual ~Animator();

	public:
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	public:
		void CreateAnimation(Texture* tex, const std::wstring& key
			, Vector2 startPos, Vector2 texSize, Vector2 interval, float delay, UINT texCnt);
		Animation* FindAnimation(const std::wstring& key);
		void PlayAnimation(const std::wstring& key, bool loop);
		void StopAnimation(const std::wstring& key);

	private:
		std::map<std::wstring, Animation*>		mAnimations;
		Animation*								mCurAnimation;
		bool									mbLoop;
	};

}