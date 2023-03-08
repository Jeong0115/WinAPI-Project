#include "zzFirstScene.h"
#include "zzApplication.h"
#include "zzSceneMgr.h"
#include "zzKey.h"

namespace zz
{
	FirstScene::FirstScene()
		: mTex(nullptr)
	{
	}
	FirstScene::~FirstScene()
	{
	}
	void FirstScene::Initialize()
	{
		mTex = ResourceMgr::Load<Texture>(L"key", L"..\\Resources\\key.bmp");
	}

	void FirstScene::Update()
	{
		if (KEY(ENTER, UP))
		{
			SceneMgr::LoadScene(eSceneType::TITLE);
		}
	}

	void FirstScene::Render(HDC hdc)
	{
		BitBlt(hdc, 0, 0, mTex->GetWidth(),
			mTex->GetHeight(), mTex->GetHdc(), 0, 0, SRCCOPY);
	}

	void FirstScene::Release()
	{
	}

	void FirstScene::Enter()
	{
	}

	void FirstScene::Exit()
	{
		HDC mBitMapHdc = Application::GetBitMapHdc();
		Rectangle(mBitMapHdc, -1, -1, 257, 385);
	}
}