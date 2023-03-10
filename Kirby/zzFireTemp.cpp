#include "zzFireTemp.h"
#include "zzTexture.h"
#include "zzTime.h"

namespace zz
{
	FireTemp::FireTemp()
	{
		mAni = AddComponent<Animator>();
		mAni->SetFix();
		mPassedTime = 0.f;
		SetPos(Vector2(128.f, 193.f));

		Texture* Fire_Temp = ResourceMgr::Load<Texture>(L"Fire_Temp", L"..\\Resources\\Fire_Temp.bmp");

		mAni->CreateAnimation(Fire_Temp, L"Fire_Temp", Vector2(12.f, 0.f), Vector2(42.f, 50.f), Vector2(42.f, 0.f), 0.04f, 13);
		mAni->PlayAnimation(L"Fire_Temp",true);

	}
	FireTemp::~FireTemp()
	{
	}
	void FireTemp::Update()
	{
		mPassedTime += Time::DeltaTime();
		Vector2 pos = GetPos();

		pos.y += Time::DeltaTime() * 100.f;

		SetPos(pos);

		if (!IsDead())
		{
			if (mPassedTime > 1.0f)
			{
				DeleteObject(this, eLayerType::ITEM);
			}
		}
		GameObject::Update();
	}
	void FireTemp::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}
