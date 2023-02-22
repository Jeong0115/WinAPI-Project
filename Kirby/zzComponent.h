#pragma once

#include "zzEngine.h"
#include "zzTexture.h"

namespace zz
{
	class Component
	{
	public:
		Component();
		virtual ~Component();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc, Vector2 pos);
		virtual void Release();

	private:
	};
}
