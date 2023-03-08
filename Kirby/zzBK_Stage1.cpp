#include "zzBK_Stage1.h"


namespace zz
{
	BK_Stage1::BK_Stage1()
		: mTex(nullptr)
	{
	}

	BK_Stage1::~BK_Stage1()
	{
	}

	void BK_Stage1::Initialize()
	{
		mTex = ResourceMgr::Load<Texture>(L"BK_Stage1", L"..\\Resources\\World1_Backgrounds.bmp");
	}

	void BK_Stage1::Update()
	{
	}

	void BK_Stage1::Render(HDC hdc)
	{
		Vector2 vPos = GetPos();
		vPos = Camera::GetRenderPos(vPos);
		//if ((vPos.x / 6.f) - (int)(vPos.x / 6) )
		TransparentBlt(hdc, (int)(vPos.x ) - 2, (int)vPos.y - 8, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));
	}

	void BK_Stage1::Release()
	{
	}
}