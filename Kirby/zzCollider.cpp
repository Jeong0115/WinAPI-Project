#include "zzCollider.h"
#include "zzGameObject.h"

#include "zzApplication.h"
#include "zzSelectGDI.h"

namespace zz
{
	Collider::Collider()
		: Component(eCompType::COLLIDER)
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

	}

	void Collider::Render(HDC hdc)
	{
		//SelectGDI pen(hdc, Application::GetPen());
		SelectGDI brush(hdc, Application::GetHollowBrush());

		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc, mPos.x - mScale.x / 2.f, mPos.y - mScale.y / 2.f
			, mPos.x + mScale.x / 2.f, mPos.y + mScale.y / 2.f);

		SelectObject(hdc, oldPen);
		//Application::SetPen(Application::GetGreenPen());

	}

	void Collider::Release()
	{
	}
}