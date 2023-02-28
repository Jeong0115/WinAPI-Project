#pragma once

#include "zzGameObject.h"
#include "zzKirby.h"

namespace zz
{
	class Skill : public GameObject
	{
	public:
		Skill();
		virtual ~Skill();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		//virtual void Release() override;

		int GetDir() { return mDir; }

		Kirby* kirby;

		

	private:
		int type;
		int mDir;
		std::vector<Skill*> mKirbySkills;
	};

}
