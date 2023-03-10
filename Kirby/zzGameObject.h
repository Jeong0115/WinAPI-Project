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
		Vector2 GetPos() { return mPos; }
		Vector2 GetScale() { return mScale; }
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetScale(Vector2 scale) { mScale = scale; }
		void SetDir(int dir) { mDir = dir; }
		int GetDir() { return mDir; }

		eLayerType GetLayerType() { return mLayerType; }
		void SetLayerType(eLayerType type) { mLayerType = type; }

		bool IsDead() { if (mState == eState::DEAD) return true; else return false; }
		bool IsChagne() { if (mState == eState::CHANGE) return true; else return false; }
		bool IsActive() { if (mState == eState::ACTIVE) return true; else return false; }

		eState GetState() { return mState; }
		void SetState(eState state) { mState = state; } //수정예정

		eAbillityType GetType() { return mAbillityType; }
		void SetType(eAbillityType type) { mAbillityType = type; }

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
		eAbillityType			mAbillityType;
		eState					mState;

		int						mDir;
	};
}

