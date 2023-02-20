#pragma once

#include "zzEntity.h"
#include "zzComponent.h"

namespace zz
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	protected:
		Vector2 mPos;

	private:
		std::vector<Component*> mComponents;
	};
}

