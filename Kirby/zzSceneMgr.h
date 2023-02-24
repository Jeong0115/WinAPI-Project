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
		static void Release();

	public:
		static Scene* GetNowScene() { return mCurScene; }
		static void LoadScene(eSceneType type) { mCurScene = mScenes[(UINT)type]; }

	private:
		static std::vector<Scene*>	mScenes;
		static Scene* mCurScene;
	};
}

