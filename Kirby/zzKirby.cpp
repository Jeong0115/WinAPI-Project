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
		: bMissileType(true)
	{
	}

	Kirby::~Kirby()
	{
	}

	void Kirby::Initialize()
	{
		
		//mComponents
		mComponents.push_back(new kirbyComponent);

		GameObject::Initialize();
		kirbyTexture = ResourceMgr::Load<Texture>(L"Kirby_Right", L"..\\Resources\\Kirby_Right.bmp");

		SetPos(Vector2(10, 130));
		SetScale(Vector2(100, 100));
	}

	void Kirby::Update()
	{
		GameObject::Update();

		Vector2 vPos = GetPos();

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

		/*if (KEY(Z, DOWN))
		{
			bMissileType = !bMissileType;
		}

		if (KEY(X, DOWN))
		{
			if (bMissileType)
				CreateMissile();
			else
				CreateMissileV2();
		}*/

		SetPos(vPos);
	}

	void Kirby::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Vector2 vPos = GetPos();
		Vector2 vScale = GetScale();

		HPEN pen = CreatePen(PS_SOLID, 5, RGB(30, 100, 20));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		//BitBlt(hdc, vPos.x , vPos.y, kirbyTexture->GetWidth(), kirbyTexture->GetHeight(), kirbyTexture->GetHdc(), 0, 0, SRCCOPY);

		TransparentBlt(hdc, vPos.x, vPos.y, kirbyTexture->GetWidth(), 
			kirbyTexture->GetHeight(), kirbyTexture->GetHdc(), 0, 0, 
			kirbyTexture->GetWidth(), kirbyTexture->GetHeight(), RGB(255, 255, 255));
		

		SelectObject(hdc, oldPen);
		DeleteObject(pen);
	}

	void Kirby::CreateMissile()
	{
		Vector2 vPos = GetPos();

		vPos.x = GetPos().x;
		vPos.y = GetPos().y + GetScale().y / 2.f;

		Missile* missile = new Missile();

		missile->SetPos(vPos);
		missile->SetScale(Vector2(25.f, 25.f));
		missile->SetDir(false);

		SceneMgr::GetNowScene()->AddGameObject(missile, eLayerType::EFFECT);
	}

	void Kirby::CreateMissileV2()
	{
		Vector2 vPos = GetPos();

		vPos.x = GetPos().x;
		vPos.y = GetPos().y + GetScale().y / 2.f;

		MissileV2* leftMissile	 = new MissileV2();
		MissileV2* centerMissile = new MissileV2();
		MissileV2* rightMissile  = new MissileV2();

		leftMissile->SetPos(Vector2(vPos.x - 20, vPos . y));
		leftMissile->SetScale(Vector2(25.f, 25.f));
		leftMissile->SetDir(false);

		centerMissile->SetPos(Vector2(vPos.x, vPos.y + 30));
		centerMissile->SetScale(Vector2(25.f, 25.f));
		centerMissile->SetDir(false);

		rightMissile->SetPos(Vector2(vPos.x + 20, vPos.y));
		rightMissile->SetScale(Vector2(25.f, 25.f));
		rightMissile->SetDir(false);

		SceneMgr::GetNowScene()->AddGameObject(leftMissile, eLayerType::EFFECT);
		SceneMgr::GetNowScene()->AddGameObject(centerMissile, eLayerType::EFFECT);
		SceneMgr::GetNowScene()->AddGameObject(rightMissile, eLayerType::EFFECT);
	}
}