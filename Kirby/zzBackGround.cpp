#include "zzBackGround.h"

namespace zz
{
	BackGround::BackGround()
	{
	}
	BackGround::~BackGround()
	{
	}

	void BackGround::Initialize()
	{
		GameObject::Initialize();

		mBKTexture = ResourceMgr::Load<Texture>(L"stage1", L"..\\Resources\\Ground.bmp");

		SetPos(Vector2(0, 0));
		//SetScale(Vector2(100, 100));
	}

	void BackGround::Update()
	{
	}

	void BackGround::Render(HDC hdc)
	{
		Vector2 vPos = GetPos();
		BitBlt(hdc, vPos.x, vPos.y, mBKTexture->GetWidth(), mBKTexture->GetHeight(), mBKTexture->GetHdc(), 0, 0, SRCCOPY);
	}

	void BackGround::Release()
	{
	}
}