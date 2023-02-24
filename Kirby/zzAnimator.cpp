#include "zzAnimator.h"

namespace zz
{
	Animator::Animator()
		: Component(eCompType::ANIMATOR)
		, mCurAnimation(nullptr)
		, mRepeat(false)
	{
	}

	Animator::~Animator()
	{
	}

	void Animator::Update()
	{
		if(mCurAnimation!=nullptr)
		{
			mCurAnimation->Update(mPos);

			if (mRepeat && mCurAnimation->IsFinish())
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
		for (auto pair : mAnimations)
		{
			delete pair.second;
			pair.second == nullptr;
		}
	}

	void Animator::CreateAnimation(Texture* tex, const std::wstring& key
		, Vector2 startPos, Vector2 texSize, Vector2 interval, float delay, UINT texCnt)
	{
		if (FindAnimation(key) != nullptr)
			assert(true);

		Animation* ani = new Animation;
		ani->SetKey(key);
		mAnimations.insert(std::make_pair(key, ani));

		ani->CreateAnimation(tex, startPos, texSize, interval, delay, texCnt);
	}

	Animation* Animator::FindAnimation(const std::wstring& key)
	{
		std::map<std::wstring, Animation*>::iterator iter = mAnimations.find(key);
	
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& key, bool repeat)
	{
		mCurAnimation = FindAnimation(key);
		mRepeat = repeat;
	}

	void Animator::StopAnimation(const std::wstring& key)
	{
		mCurAnimation = FindAnimation(key);
		mCurAnimation->SetFinish(true);
		mRepeat = false;
	}
}