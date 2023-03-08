#pragma once

//#include "zzEngine.h"
#include "zzEventMgr.h"
namespace zz
{
	class GameObject;

	void CreateObject(GameObject* obj, eLayerType type);
	void DeleteObject(GameObject* obj, eLayerType type);


	/*template<typename T>
	void CreateObject(eLayerType type)
	{
		EventInfo event = {};

		T* obj = new T();

		event.eventType = eEventType::CREATE_OBJ;
		event.objPointer = (DWORD_PTR)obj;
		event.objLayer = (DWORD_PTR)type;

		EventMgr::AddEvent(event);
	}

	template<typename T>
	void CreateObject(eLayerType type, Vector2 pos)
	{
		EventInfo event = {};

		T* obj = new T();

		event.eventType = eEventType::CREATE_OBJ;
		event.objPointer = (DWORD_PTR)obj;
		event.objLayer = (DWORD_PTR)type;

		obj->SetPos(pos);

		EventMgr::AddEvent(event);
	}


	template<typename T>
	void CreateObject(eLayerType type, Vector2 pos, int dir)
	{
		EventInfo event = {};

		T* obj = new T();

		event.eventType = eEventType::CREATE_OBJ;
		event.objPointer = (DWORD_PTR)obj;
		event.objLayer = (DWORD_PTR)type;

		obj->SetPos(pos);
		obj->SetDir(dir);

		EventMgr::AddEvent(event);
	}*/
}