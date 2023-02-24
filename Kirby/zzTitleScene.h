#pragma once

#include "zzScene.h"
#include "zzSceneMgr.h"

namespace zz
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Exit();

	private:
		Texture* mTex;
	};
}

