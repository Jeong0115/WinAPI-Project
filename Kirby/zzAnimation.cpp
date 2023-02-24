#include "zzAnimation.h"
#include "zzTime.h"

namespace zz
{
	Animation::Animation()
		: mCurFrame(0)
		, mTime(0)
		, mFinish(false)
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Update(Vector2 pos)
	{
		if (mFinish)
			return;

		mPos = pos;
		mTime += Time::DeltaTime();

		if (mFrames[mCurFrame].delay < mTime)
		{
			mTime -= mFrames[mCurFrame].delay;
			mCurFrame++;
			if (mCurFrame >= mFrames.size())
			{
				mCurFrame = -1;
				mFinish = true;
			}
		}
	}

	void Animation::Render(HDC hdc)
	{
		if (mFinish)
			return;

		TransparentBlt(hdc, mPos.x - mFrames[mCurFrame].texSize.x / 2.f, mPos.y - mFrames[mCurFrame].texSize.y / 2.f
			, mFrames[mCurFrame].texSize.x, mFrames[mCurFrame].texSize.y, mTex->GetHdc()
			, mFrames[mCurFrame].pos.x, mFrames[mCurFrame].pos.y
			, mFrames[mCurFrame].texSize.x, mFrames[mCurFrame].texSize.y, RGB(255, 0, 255));
	}

	void Animation::CreateAnimation(Texture* tex, Vector2 startPos
		, Vector2 texSize, Vector2 interval, float delay,  UINT texCnt)
	{
		mTex = tex;

		FrameInfo frame;
		for (UINT i = 0; i < texCnt; i++)
		{
			frame.delay = delay;
			frame.texSize = texSize;
			frame.pos = startPos + interval * i;

			mFrames.push_back(frame);
		}
	}
}