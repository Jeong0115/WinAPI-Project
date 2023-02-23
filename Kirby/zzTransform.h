#pragma once

#include "zzComponent.h"

namespace zz
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	public:
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetScale(Vector2 size) { mScale = size; }
		Vector2 GetPos() { return mPos; }
		Vector2 GetScale() { return mScale; }


	private:
		Vector2 mPos;
		Vector2 mScale;
	};
}

