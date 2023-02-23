#include "zzKirby.h"
#include "zzTime.h"
#include "zzKey.h"

#include "zzMissile.h"
#include "zzMissileV2.h"
#include "zzSceneMgr.h"
#include "zzScene.h"
#include "zzkirbyComponent.h"


namespace zz
{
	Kirby::Kirby()
		: kirbyTexture(nullptr)
		, mTr(nullptr)
	{
	}

	Kirby::~Kirby()
	{
	}

	void Kirby::Initialize()
	{
		
		//mComponents
		//mComponents.push_back(new kirbyComponent);
		mTr = AddComponent<Transform>();
		mColli = AddComponent<Collider>();

		kirbyTexture = ResourceMgr::Load<Texture>(L"Kirby_Right", L"..\\Resources\\Kirby_Right.bmp");

		mTr->SetPos(Vector2(10, 140));
		mTr->SetScale(Vector2(20, 18));

		mColli->SetPos(mTr->GetPos());
		mColli->SetScale(mTr->GetScale());

		GameObject::Initialize();
	}

	void Kirby::Update()
	{
		GameObject::Update();

		Vector2 vPos = mTr->GetPos();

		if (KEY(LEFT, PRESSED))
		{
			kirbyTexture = ResourceMgr::Load<Texture>(L"Kirby_Left", L"..\\Resources\\Kirby_Left.bmp");
			vPos.x -= 100.f * Time::DeltaTime();
		}

		if (KEY(RIGHT, PRESSED))
		{
			vPos.x += 100.f * Time::DeltaTime();
			kirbyTexture = ResourceMgr::Load<Texture>(L"Kirby_Right", L"..\\Resources\\Kirby_Right.bmp");
		}

		if (KEY(UP, PRESSED))
		{
			vPos.y -= 100.f * Time::DeltaTime();
		}

		if (KEY(DOWN, PRESSED))
		{
			vPos.y += 100.f * Time::DeltaTime();
		}

		mTr->SetPos(vPos);
		mColli->SetPos(vPos);
		
	}

	void Kirby::Render(HDC hdc)
	{
		

		Vector2 vPos = mTr->GetPos();
		Vector2 vScale = mTr->GetScale();

	/*	HPEN pen = CreatePen(PS_SOLID, 5, RGB(30, 100, 20));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);*/

		//BitBlt(hdc, vPos.x , vPos.y, kirbyTexture->GetWidth(), kirbyTexture->GetHeight(), kirbyTexture->GetHdc(), 0, 0, SRCCOPY);

		TransparentBlt(hdc, vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2.f, kirbyTexture->GetWidth(), 
			kirbyTexture->GetHeight(), kirbyTexture->GetHdc(), 0, 0, 
			kirbyTexture->GetWidth(), kirbyTexture->GetHeight(), RGB(255, 255, 255));
		
		GameObject::Render(hdc);

		/*SelectObject(hdc, oldPen);
		DeleteObject(pen);*/
	}
}