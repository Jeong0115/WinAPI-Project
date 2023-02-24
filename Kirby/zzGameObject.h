#pragma once

#include "zzEntity.h"
#include "zzComponent.h"
#include "define.h"
#include "zzTexture.h"
#include "zzResourceMgr.h"


namespace zz
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	public:
		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;

			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			for (Component* comp : mComponents)
			{
				if (dynamic_cast<T*>(comp))
					return dynamic_cast<T*>(comp);
			}

			return nullptr;
		}

		template <typename T>
		void SetComponent(T* comp)
		{
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;
		}

	private:
		std::vector<Component*> mComponents;
	};
}

