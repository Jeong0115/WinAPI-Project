#pragma once

#include "zzComponent.h"
#include "zzAnimation.h"

namespace zz
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}

			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};

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
		void PlayAnimation(const std::wstring& name, bool loop);
		void StopAnimation(const std::wstring& name);

		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);

	private:
		std::map<std::wstring, Animation*>		mAnimations;
		std::map<std::wstring, Events*>			mEvents;
		Animation*								mCurAnimation;
		bool									mbLoop;
	};

}