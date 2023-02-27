#include "zzCollider.h"
#include "zzGameObject.h"

#include "zzApplication.h"
#include "zzSelectGDI.h"

namespace zz
{
	UINT Collider::gNextID = 0;

	Collider::Collider()
		: Component(eCompType::COLLIDER)
		, mPos(Vector2(0.f, 0.f))
		, mScale(Vector2(0.f, 0.f))
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

		Rectangle(hdc, (int)(mPos.x - mScale.x / 2.f), (int)(mPos.y - mScale.y / 2.f)
			, (int)(mPos.x + mScale.x / 2.f), (int)(mPos.y + mScale.y / 2.f));

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