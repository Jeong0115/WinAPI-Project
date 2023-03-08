#pragma once

#include "zzScene.h"

namespace zz
{
	class Texture;
	class FirstScene : public Scene
	{
	public:
		FirstScene();
		virtual ~FirstScene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void Enter();
		virtual void Exit();

	private:
		Texture* mTex;
	};
}

