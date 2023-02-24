#pragma once

#include "zzComponent.h"

namespace zz
{
	class kirbyComponent : public Component
	{
	public:
		kirbyComponent();
		virtual ~kirbyComponent();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	public:
		void SetPos(Vector2 pos) { mPos = pos; }

		Vector2 GetPos() { return mPos; }

	private:
		Texture* ice;
		std::vector<Texture*> icy;
		int idx;
		float sec;
		bool bPress;
		Vector2 mPos;
	};

}
