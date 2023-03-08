#include "zzHP.h"

namespace zz
{
	HP::HP()
	{
	}

	HP::~HP()
	{
	}

	void HP::Initialize()
	{
		mTex = ResourceMgr::Load<Texture>(L"111", L"..\\Resources\\111.bmp");
	}

	void HP::Update()
	{

	}

	void HP::Render(HDC hdc)
	{
		TransparentBlt(hdc, 45, 164, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0 , 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));
	}
}