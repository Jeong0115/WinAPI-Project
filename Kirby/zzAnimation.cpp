#include "zzAnimation.h"
#include "zzTime.h"
#include "zzCamera.h"

namespace zz
{
	Animation::Animation()
		: mCurFrame(0)
		, mTime(0)
		, mFinish(false)
		, mTex(nullptr)
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Update(Vector2 pos)
	{
		if (mFinish)
			return;

		mPos = Camera::GetRenderPos(pos);
		//mPos = pos;
		mTime += Time::DeltaTime();

		if (mFrames[mCurFrame].delay < mTime)
		{
			mTime -= mFrames[mCurFrame].delay;
			mCurFrame++;
			if (mCurFrame >= mFrames.size())
			{
				mCurFrame = 0;
				mFinish = true;
			}
		}
	}

	void Animation::Render(HDC hdc)
	{
		if (mFinish)
			return;

		TransparentBlt(hdc, (int)(mPos.x - mFrames[mCurFrame].texSize.x / 2.f)
			, (int)(mPos.y - mFrames[mCurFrame].texSize.y)
			, (int)(mFrames[mCurFrame].texSize.x)	, (int)(mFrames[mCurFrame].texSize.y), mTex->GetHdc()
			, (int)(mFrames[mCurFrame].pos.x)		, (int)(mFrames[mCurFrame].pos.y)
			, (int)(mFrames[mCurFrame].texSize.x)	, (int)(mFrames[mCurFrame].texSize.y), RGB(255, 0, 255));
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
			frame.pos = startPos + interval * (int)i;

			frame.offset.x = texSize.x / 2.f;
			frame.offset.y = texSize.y;

			mFrames.push_back(frame);
		}
	}
}