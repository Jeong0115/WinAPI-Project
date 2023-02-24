#include "zzTitleScene.h"
#include "zzKey.h"
#include "zzSceneMgr.h"
#include "zzTexture.h"
#include "zzApplication.h"

namespace zz
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		mTex= ResourceMgr::Load<Texture>(L"Title", L"..\\Resources\\TitleScene.bmp");
	}

	void TitleScene::Update()
	{
		if (KEY(ENTER, UP))
		{
			SceneMgr::LoadScene(eSceneType::PLAY);
		}
		Exit();
	}

	void TitleScene::Render(HDC hdc)
	{
		BitBlt(hdc, 0, 0, mTex->GetWidth(),
			mTex->GetHeight(), mTex->GetHdc(), 8, 0, SRCCOPY);
	}

	void TitleScene::Exit()
	{
		HDC mBitMapHdc = Application::GetBitMapHdc();
		Rectangle(mBitMapHdc, -1, -1, 1280, 720);
	}
}