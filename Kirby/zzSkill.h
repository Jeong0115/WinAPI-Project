#pragma once

#include "zzGameObject.h"
#include "zzKirby.h"

namespace zz
{
	class Skill : public GameObject
	{
	public:
		Skill(Kirby* kirby);
		virtual ~Skill();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		//virtual void Release() override;

		int GetDir() { return mDir; }

	private:
		int							mType;
		int							mDir;
		std::vector<GameObject*>	mKirbySkills;
		Kirby*						mKirby;
	};

}
