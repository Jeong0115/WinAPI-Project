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
		Vector2 GetPos() { return mPos; }
		Vector2 GetScale() { return mScale; }
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetScale(Vector2 scale) { mScale = scale; }

		bool IsDeactivate() { return !mbActivate; }

	private:
		void SetDeactivate() { mbActivate = false; }

		friend class EventMgr;

	public:
		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;
			comp->SetOwner(this);

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
		bool					mbActivate;
		Vector2					mPos;
		Vector2					mScale;
	};
}

