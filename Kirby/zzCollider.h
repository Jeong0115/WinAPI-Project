#pragma once

#include "zzComponent.h"
 

namespace zz
{
	class GameObject;

	class Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	public:
		void SetScale(Vector2 scale) { mScale = scale; }
		void SetPos(Vector2 pos) { mPos = pos; }

		Vector2 GetScale() { return mScale; }
		Vector2 GetPos() { return mPos; }


		HPEN& GetPen() { return pen; }

	private:
		//Vector2 mOffsetPos;
		Vector2 mPos;
		Vector2 mScale;
		HPEN pen;
	};

}
