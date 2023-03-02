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

	/*Collider::Collider(const Collider& origin)
	{
	}*/

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
		

		//pen = CreatePen(PS_SOLID, 10 ,RGB(13, 44, 33));
		//HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Vector2 pos = GetOwner()->GetPos();
		Vector2 scale = GetOwner()->GetScale();

		Rectangle(hdc, (int)(pos.x - scale.x / 2.f), (int)(pos.y - scale.y)
			, (int)(pos.x + scale.x / 2.f), (int)(pos.y));

		//SelectObject(hdc, oldPen);
		//DeleteObject(pen);
		//Application::SetPen(Application::GetGreenPen());

	}

	void Collider::Release()
	{
	}
	void Collider::OnCollision()
	{
	}
	void Collider::OnCollisionEnter()
	{
		mColliCnt++;
	}
	void Collider::OnCollisionExit()
	{
		mColliCnt--;
	}
}