#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Stage1 : public GameObject
	{
	public:
		Stage1();
		virtual ~Stage1();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
		Texture* mTex;
	};
}

