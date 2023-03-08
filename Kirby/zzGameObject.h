#pragma once

#include "zzEntity.h"
#include "zzComponent.h"
#include "define.h"
#include "zzResourceMgr.h"
#include "zzCamera.h"
#include "zzFunction.h"
//#include "zzEngine.h"

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

		virtual void OnCollisionEnter(GameObject* other) {}
		virtual void OnCollision(GameObject* other) {}
		virtual void OnCollisionExit(GameObject* other) {}

	public:
		virtual Vector2 GetPos() { return mPos; }
		virtual Vector2 GetScale() { return mScale; }
		virtual void SetPos(Vector2 pos) { mPos = pos; }
		virtual void SetScale(Vector2 scale) { mScale = scale; }
		virtual void SetDir(int dir) { mDir = dir; }
		virtual int GetDir() { return mDir; }

		eLayerType GetLayerType() { return mLayerType; }
		void SetLayerType(eLayerType type) { mLayerType = type; }

		bool IsDead() { if (mState == eState::DEAD) return true; else return false; }
		bool IsChagne() { if (mState == eState::CHANGE) return true; else return false; }
		bool IsActive() { if (mState == eState::ACTIVE) return true; else return false; }

		virtual eState GetState() { return mState; }
		virtual void SetState(eState state) { mState = state; } //수정예정

	protected:
		void SetDead() { mState = eState::DEAD; }

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
		Vector2					mPos;
		Vector2					mScale;
		eLayerType				mLayerType;
		eState					mState;
		int						mDir;
	};
}

