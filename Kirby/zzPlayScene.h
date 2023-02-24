#pragma once

#include "zzScene.h"
#include "zzTexture.h"

namespace zz
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Exit();

	private:
		Texture* mTex;
	};
}

