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
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	public:
		void CreateAnimation(Texture* tex, const std::wstring& key
			, Vector2 startPos, Vector2 texSize, Vector2 interval, float delay, UINT texCnt);
		Animation* FindAnimation(const std::wstring& key);
		void PlayAnimation(const std::wstring& key, bool repeat);
		void StopAnimation(const std::wstring& key);

		Vector2 GetPos() { return mPos; }
		void SetPos(Vector2 pos) { mPos = pos; }

	private:
		std::map<std::wstring, Animation*>	 mAnimations;
		Animation*							 mCurAnimation;
		Vector2	mPos;
		bool mRepeat;
	};

}