#include "zzSceneMgr.h"
#include "zzPlayScene.h"
#include "zzPauseScene.h"
#include "zzTitleScene.h"
#include "zzToolScene.h"
namespace zz
{
	std::vector<Scene*> SceneMgr::mScenes = {};
	Scene* SceneMgr::mCurScene = {};

	SceneMgr::SceneMgr()
	{
	}

	SceneMgr::~SceneMgr()
	{
		
	}

	void SceneMgr::Initialize()
	{
		mScenes.resize((UINT)eSceneType::MAX);

		mScenes[(UINT)eSceneType::TITLE] = new TitleScene;
		mScenes[(UINT)eSceneType::TOOL] = new ToolScene;
		mScenes[(UINT)eSceneType::PLAY] = new PlayScene;
		mScenes[(UINT)eSceneType::PAUSE] = new PauseScene;

		mScenes[(UINT)eSceneType::PLAY]->SetName(L"Play Scene");

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			scene->Initialize();
		}

		mCurScene = mScenes[(UINT)eSceneType::TITLE];

		//mCurScene->Initialize();
	}

	void SceneMgr::Update()
	{
		/*for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			scene->Update();
		}*/
		mCurScene->Update();
	}

	void SceneMgr::Render(HDC hdc)
	{
		/*for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			scene->Render(hdc);
		}*/
		mCurScene->Render(hdc);
	}

	void SceneMgr::Release()
	{
		for (UINT i = 0; i < (UINT)eSceneType::MAX; i++)
		{
			if (mScenes[i] == nullptr) continue;
			delete mScenes[i];
		}
	}

	void SceneMgr::LoadScene(eSceneType type)
	{
		mCurScene->Exit();
		mCurScene = mScenes[(UINT)type];
		mCurScene->Enter();
	}
}
