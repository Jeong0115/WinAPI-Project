#include "zzStage1.h"

namespace zz
{
	Stage1::Stage1()
		: mTex(nullptr)
	{
	}
	Stage1::~Stage1()
	{
	}

	void Stage1::Initialize()
	{
		GameObject::Initialize();

		mTex = ResourceMgr::Load<Texture>(L"Stage1-1", L"..\\Resources\\Level 1-1 Foreground (2).bmp");

		SetPos(Vector2(0.f, 0.f));
		//SetScale(Vector2(100, 100));
	}

	void Stage1::Update()
	{
		//GameObject::Update();
	}

	void Stage1::Render(HDC hdc)
	{
		Vector2 vPos = GetPos();
		vPos = Camera::GetRenderPos(vPos);
		TransparentBlt(hdc, (int)vPos.x - 5, (int)vPos.y - 5, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255,0,255));
		//GameObject::Render(hdc);
	}

	void Stage1::Release()
	{
	}
}