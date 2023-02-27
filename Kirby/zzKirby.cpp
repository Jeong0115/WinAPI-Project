#include "zzKirby.h"
#include "zzTime.h"
#include "zzKey.h"

#include "zzSceneMgr.h"
#include "zzScene.h"
#include "zzkirbyComponent.h"


namespace zz
{
	Kirby::Kirby()
		: mTex(nullptr)
		, mTr(nullptr)
		, mColli(nullptr)
		, mAni(nullptr)
		, state(0)
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
		//kir = AddComponent<kirbyComponent>();
		mAni = AddComponent<Animator>();


		//mTex = ResourceMgr::Load<Texture>(L"Kirby_Right", L"..\\Resources\\Kirby_Right.bmp");

		//Texture* tex = ResourceMgr::Load<Texture>(L"Kirby", L"..\\Resources\\Kirby.bmp");

		Texture* FireKirbyStayRight = ResourceMgr::Load<Texture>(L"FireKirbyStayRight", L"..\\Resources\\FireKirby_Staty_Right.bmp");
		Texture* FireKirbyStayLeft = ResourceMgr::Load<Texture>(L"FireKirbyStayLeft", L"..\\Resources\\FireKirby_Staty_Left.bmp");
		Texture* FireKirbyWalkRight = ResourceMgr::Load<Texture>(L"FireKirbyWalkRight", L"..\\Resources\\FireKirby_Walk_Right.bmp");
		Texture* FireKirbyWalkLeft = ResourceMgr::Load<Texture>(L"FireKirbyWalkLeft", L"..\\Resources\\FireKirby_Walk_Left.bmp");

		Texture* IceKirbyStayRight = ResourceMgr::Load<Texture>(L"IceKirbyStayRight", L"..\\Resources\\IceKirby_Staty_Right.bmp");
		Texture* IceKirbyStayLeft = ResourceMgr::Load<Texture>(L"IceKirbyStayLeft", L"..\\Resources\\IceKirby_Staty_Left.bmp");
		Texture* IceKirbyWalkRight = ResourceMgr::Load<Texture>(L"IceKirbyWalkRight", L"..\\Resources\\IceKirby_Walk_Right.bmp");
		Texture* IceKirbyWalkLeft = ResourceMgr::Load<Texture>(L"IceKirbyWalkLeft", L"..\\Resources\\IceKirby_Walk_Left.bmp");

		


		mStayRightKeys.push_back(L"FireKirbyStayRight");
		mStayLeftKeys.push_back(L"FireKirbyStayLeft");
		mStayRightKeys.push_back(L"IceKirbyStayRight");
		mStayLeftKeys.push_back(L"IceKirbyStayLeft");

		mWalkRightKeys.push_back(L"FireKirbyWalkRight");
		mWalkLeftKeys.push_back(L"FireKirbyWalkLeft");
		mWalkRightKeys.push_back(L"IceKirbyWalkRight");
		mWalkLeftKeys.push_back(L"IceKirbyWalkLeft");

		//mAni->CreateAnimation(tex,L"Kirby", Vector2(0.f, 0.f), Vector2(21.6f, 31.f), Vector2(21.6f, 0.f), 0.13f, 10);
		mAni->CreateAnimation(FireKirbyStayRight, L"FireKirbyStayRight", Vector2(0.f, 0.f), Vector2(26.375f, 33.f), Vector2(26.375f, 0.f), 0.2f, 8);
		mAni->CreateAnimation(FireKirbyStayLeft, L"FireKirbyStayLeft", Vector2(184.625f, 0.f), Vector2(26.375f, 33.f), Vector2(-26.375f, 0.f), 0.2f, 8);
		mAni->CreateAnimation(FireKirbyWalkRight, L"FireKirbyWalkRight", Vector2(0.f, 0.f), Vector2(27.3f, 37.f), Vector2(27.35f, 0.f), 0.05f, 20);
		mAni->CreateAnimation(FireKirbyWalkLeft, L"FireKirbyWalkLeft", Vector2(518.7f, 0.f), Vector2(27.3f, 37.f), Vector2(-27.35f, 0.f), 0.05f, 20);

		mAni->CreateAnimation(IceKirbyStayRight, L"IceKirbyStayRight", Vector2(0.f, 0.f), Vector2(26.f, 29.f), Vector2(26.f, 0.f), 0.2f, 2);
		mAni->CreateAnimation(IceKirbyStayLeft, L"IceKirbyStayLeft", Vector2(26.f, 0.f), Vector2(26.f, 29.f), Vector2(-26.f, 0.f), 0.2f, 2);
		mAni->CreateAnimation(IceKirbyWalkRight, L"IceKirbyWalkRight", Vector2(0.f, 0.f), Vector2(26.f, 27.f), Vector2(26.f, 0.f), 0.05f, 10);
		mAni->CreateAnimation(IceKirbyWalkLeft, L"IceKirbyWalkLeft", Vector2(234.f, 0.f), Vector2(26.f, 27.f), Vector2(-26.f, 0.f), 0.05f, 10);

		


		mTr->SetPos(Vector2(10, 130));
		mTr->SetScale(Vector2(20, 18));

		mColli->SetPos(mTr->GetPos());
		mColli->SetScale(mTr->GetScale());

		mAni->SetPos(mTr->GetPos());

		//kir->SetPos(mTr->GetPos());

		GameObject::Initialize();
	}

	void Kirby::Update()
	{
		Vector2 vPos = mTr->GetPos();

		if (KEY(LEFT, PRESSED))
		{
			vPos.x -= (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(mWalkLeftKeys[state], true);
		}


		if (KEY(LEFT, UP))
		{
			mAni->PlayAnimation(mStayLeftKeys[state], true);
		}

		if (KEY(RIGHT, PRESSED))
		{
			vPos.x += (float)(100.f * Time::DeltaTime());
			mAni->PlayAnimation(mWalkRightKeys[state], true);
		}

		if (KEY(RIGHT, UP))
		{
			//mAni->StopAnimation(L"Kirby");
			mAni->PlayAnimation(mStayRightKeys[state], true);
		}

		if (KEY(Z, DOWN))
		{
			state++;
			if (state > 1)
				state = 0;
			//mAni->PlayAnimation(L"TransformEffect", true);
		}

		//if (KEY(UP, PRESSED))
		//{
		//	vPos.y -= 100.f * Time::DeltaTime();
		//}

		//if (KEY(DOWN, PRESSED))
		//{
		//	vPos.y += 100.f * Time::DeltaTime();
		//}

		mTr->SetPos(vPos);
		//kir->SetPos(vPos);
		mColli->SetPos(vPos);
		mAni->SetPos(vPos);

		GameObject::Update();
		
	}

	void Kirby::Render(HDC hdc)
	{
		

		/*Vector2 vPos = mTr->GetPos();
		Vector2 vScale = mTr->GetScale();*/

	/*	HPEN pen = CreatePen(PS_SOLID, 5, RGB(30, 100, 20));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);*/

		//BitBlt(hdc, vPos.x , vPos.y, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc(), 0, 0, SRCCOPY);

		/*TransparentBlt(hdc, vPos.x - vScale.x / 2.f, vPos.y - vScale.y / 2.f, mTex->GetWidth(), 
			mTex->GetHeight(), mTex->GetHdc(), 0, 0, 
			mTex->GetWidth(), mTex->GetHeight(), RGB(255, 255, 255));*/
		
		GameObject::Render(hdc);

		/*SelectObject(hdc, oldPen);
		DeleteObject(pen);*/
	}
}