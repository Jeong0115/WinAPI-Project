#pragma once

#include "zzGameObject.h"

namespace zz
{
	class BackGround : public GameObject
	{
	public:
		BackGround();
		virtual ~BackGround();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
		Texture* mBKTexture;
	};
}

