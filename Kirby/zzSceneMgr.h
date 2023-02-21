#pragma once

#include "zzScene.h"

namespace zz
{
	class SceneMgr
	{
	public:
		SceneMgr();
		virtual ~SceneMgr();

	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

	public:
		static Scene* GetNowScene() { return mNowScene; }

	private:
		static std::vector<Scene*>	mScenes;
		static Scene* mNowScene;
	};
}

