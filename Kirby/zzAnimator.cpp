#include "zzAnimator.h"
#include "zzGameObject.h"

namespace zz
{

	Animator::Animator()
		: Component(eCompType::ANIMATOR)
		, mCurAnimation(nullptr)
		, mbLoop(false)
		, mbFix(false)
	{
	}

	Animator::~Animator()
	{
		for (auto pair : mAnimations)
		{
			delete pair.second;
			pair.second = nullptr;
		}

		for (auto pair : mEvents)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}

	void Animator::Update()
	{
		if(mCurAnimation!=nullptr)
		{
			if(mbFix)
			{
				mCurAnimation->Update(GetOwner()->GetPos());
			}
			else
			{
				mCurAnimation->Update(Camera::GetRenderPos(GetOwner()->GetPos()));
			}

			if (mCurAnimation->IsFinish())
			{
				Animator::Events* events = FindEvents(mCurAnimation->GetName());

				if (events != nullptr)
					events->mCompleteEvent();
			}
			if (mbLoop && mCurAnimation->IsFinish())
			{
				mCurAnimation->Repeat(0);
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mCurAnimation != nullptr)
		{
			mCurAnimation->Render(hdc);
		}
	}

	void Animator::Release()
	{
	}

	void Animator::CreateAnimation(Texture* tex, const std::wstring& name
		, Vector2 startPos, Vector2 texSize, Vector2 interval, float delay, UINT texCnt)
	{
		if (FindAnimation(name) != nullptr)
			assert(true);

		Animation* ani = new Animation;
		ani->SetName(name);
		mAnimations.insert(std::make_pair(name, ani));

		Events* event = new Events();
		mEvents.insert(std::make_pair(name, event));

		ani->CreateAnimation(tex, startPos, texSize, interval, delay, texCnt);
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter = mAnimations.find(name);
	
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		if (mCurAnimation != nullptr)
		{
			Animator::Events* prevEvents
				= FindEvents(mCurAnimation->GetName());

			if (prevEvents != nullptr)
				prevEvents->mEndEvent();
		}

		mCurAnimation = FindAnimation(name);
		mCurAnimation->Repeat(0);
		mbLoop = loop;

		Animator::Events* events
			= FindEvents(name);

		if (events != nullptr)
			events->mStartEvent();
	}

	void Animator::StopAnimation()
	{
		mCurAnimation->SetFinish(true);
		mbLoop = false;
	}

	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter = mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		return FindEvents(name)->mStartEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		return FindEvents(name)->mCompleteEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		return FindEvents(name)->mEndEvent.mEvent;
	}
}