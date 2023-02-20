#pragma once

#include "zzEngine.h"

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
		virtual void Render(HDC hdc);
		virtual void Release();
	};
}
