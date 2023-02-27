#pragma once

#include "zzComponent.h"
 

namespace zz
{
	class GameObject;

	class Collider : public Component
	{
	public:
		Collider();
		//Collider(const Collider& origin);
		virtual ~Collider();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	public:
		void OnCollision();
		void OnCollisionEnter();
		void OnCollisionExit();

	public:

		UINT GetID() { return mID; }

		HPEN& GetPen() { return pen; }


	private:
		//Vector2 mOffsetPos;
		HPEN		pen;
		UINT		mID;
		int			mColliCnt;
		static UINT gNextID;
	};

}
