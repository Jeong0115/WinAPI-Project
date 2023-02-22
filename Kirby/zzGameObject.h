#pragma once

#include "zzEntity.h"
#include "zzComponent.h"
#include "define.h"
#include "zzTexture.h"
#include "zzResourceMgr.h"

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

	public:
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetScale(Vector2 scale) { mScale = scale; }

		Vector2 GetPos() { return mPos; }
		Vector2 GetScale() { return mScale; }

	private:
		Vector2 mPos;
		Vector2 mScale;

	protected:
		std::vector<Component*> mComponents;
	};
}

