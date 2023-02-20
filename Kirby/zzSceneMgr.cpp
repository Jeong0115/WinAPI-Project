#include "zzSceneMgr.h"
#include "zzPlayScene.h"


namespace zz
{
	std::vector<Scene*> SceneMgr::mScenes = {};
	Scene* SceneMgr::mNowScene = {};

	SceneMgr::~SceneMgr()
	{
		for (UINT i = 0; i < (UINT)eSceneType::MAX; i++)
		{
			delete mScenes[i];
		}
	}

	void SceneMgr::Initialize()
	{
		mScenes.resize((UINT)eSceneType::MAX);
		mScenes[(UINT)eSceneType::PLAY] = new PlayScene;
		mScenes[(UINT)eSceneType::PLAY]->SetName(L"Play Scene");

		/*for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			scene->Initialize();
		}*/

		mNowScene = mScenes[(UINT)eSceneType::PLAY];

		mNowScene->Initialize();
	}

	void SceneMgr::Update()
	{
		/*for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			scene->Update();
		}*/
		mNowScene->Update();
	}

	void SceneMgr::Render(HDC hdc)
	{
		/*for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			scene->Render(hdc);
		}*/
		mNowScene->Render(hdc);
	}
}
