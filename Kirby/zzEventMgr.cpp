#include "zzEventMgr.h"
#include "zzSceneMgr.h"
#include "zzScene.h"


namespace zz
{
	std::vector<EventInfo> EventMgr::mEventsInfo = {};
	std::vector<GameObject*> EventMgr::mDeactivateList = {};

	EventMgr::EventMgr()
	{
	}

	EventMgr::~EventMgr()
	{
	}

	void EventMgr::Update() 
	{
		for (UINT i = 0; i < mDeactivateList.size(); i++)
		{
			delete mDeactivateList[i];
		}
		mDeactivateList.clear();
		for (UINT i = 0; i < mEventsInfo.size(); i++)
		{
			Execute(mEventsInfo[i]);
		}
		mEventsInfo.clear();
	}

	void EventMgr::Execute(const EventInfo event)
	{
		switch (event.eventType)
		{
		case eEventType::CREATE_OBJ:
		{
			GameObject* obj = (GameObject*)event.objPointer;
			eLayerType type = (eLayerType)event.objLayer;
			SceneMgr::GetCurScene()->AddGameObject(obj, type);
		}
			break;
		case eEventType::DELETE_OBJ:
		{
			GameObject* obj = (GameObject*)event.objPointer;
			obj->SetDead();
			mDeactivateList.push_back(obj);
		}
			break;

	
		case eEventType::SCENE_CHANGE:

			break;

		default:
			break;
		}
	}
}