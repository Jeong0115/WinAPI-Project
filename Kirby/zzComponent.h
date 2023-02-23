#pragma once

#include "zzEngine.h"
#include "zzTexture.h"
#include "zzEntity.h"


namespace zz
{
	class Component : public Entity
	{
	public:
		Component(eCompType type);
		virtual ~Component();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	public:
		eCompType GetType() { return mType; }

	private:
		const eCompType mType;
	};
}
