#include "zzEventMgr.h"
#include "zzGameObject.h"
#include "zzIceSkill.h"

namespace zz
{

	void CreateObject(GameObject* obj, eLayerType type)
	{
		EventInfo event = {};

		event.eventType = eEventType::CREATE_OBJ;
		event.objPointer = (DWORD_PTR)obj;
		event.objLayer = (DWORD_PTR)type;

		EventMgr::AddEvent(event);
	}


	/*void CreateObject(GameObject* obj, eLayerType type, int dir)
	{
		EventInfo event = {};

		obj->SetDir(dir);

		event.eventType = eEventType::CREATE_OBJ;
		event.objPointer = (DWORD_PTR)obj;
		event.objLayer = (DWORD_PTR)type;

		EventMgr::AddEvent(event);
	}*/

	void DeleteObject(GameObject* obj, eLayerType type)
	{
		EventInfo event = {};

		event.eventType = eEventType::DELETE_OBJ;
		event.objPointer = (DWORD_PTR)obj;
		event.objLayer = (DWORD_PTR)type;

		EventMgr::AddEvent(event);
	}
}
