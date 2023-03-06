#include "zzCollider.h"
#include "zzGameObject.h"

#include "zzApplication.h"
#include "zzSelectGDI.h"

namespace zz
{
	UINT Collider::gNextID = 0;

	Collider::Collider()
		: Component(eCompType::COLLIDER)
		, pen(nullptr)
		, mID(gNextID++)
		, mColliCnt(0)
	{
	}


	Collider::~Collider()
	{
	}


	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
		if (mColliCnt < 0)
			assert(false);
	}

	void Collider::Render(HDC hdc)
	{
		pen = Application::GetGreenPen();

		if(mColliCnt)
		{
			pen = Application::GetRedPen();
		}

		SelectGDI SelectPen(hdc, pen);
		SelectGDI SelectBrush(hdc, Application::GetHollowBrush());

		Vector2 pos = Camera::GetRenderPos(GetOwner()->GetPos());
		//Vector2 pos = GetOwner()->GetPos();
		Vector2 scale = GetOwner()->GetScale();

		Rectangle(hdc, (int)(pos.x - scale.x / 2.f), (int)(pos.y - scale.y)
			, (int)(pos.x + scale.x / 2.f), (int)(pos.y));
	}

	void Collider::Release()
	{
	}

	void Collider::OnCollisionEnter(GameObject* other)
	{
		mColliCnt++;
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OnCollision(GameObject* other)
	{
		GetOwner()->OnCollision(other);
	}

	void Collider::OnCollisionExit(GameObject* other)
	{
		mColliCnt--;
		GetOwner()->OnCollisionExit(other);
	}
}