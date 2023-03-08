#include "zzInventory.h"
#include "zzTexture.h"

namespace zz
{
	Inventory::Inventory()
		: mAni(nullptr)
	{
	}

	Inventory::~Inventory()
	{
	}

	void Inventory::Initialize()
	{
		mAni = AddComponent<Animator>();
		mAni->SetFix();

		Texture* Inventory = ResourceMgr::Load<Texture>(L"Inventory", L"..\\Resources\\Inventory.bmp");
		
		mAni->CreateAnimation(Inventory, L"Inventory", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.2f, 16);

		mAni->PlayAnimation(L"Inventory", true);

		SetPos(Vector2(128.f, 384.f));

		GameObject::Initialize();
	}

	void Inventory::Update()
	{
		GameObject::Update();
	}
	
	void Inventory::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}