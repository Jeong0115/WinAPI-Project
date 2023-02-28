#include "zzSkill.h"
#include "zzFireSkill.h"
#include "zzDefaultSkill.h"
#include "zzIceSkill.h"

namespace zz
{
	Skill::Skill()
	{
	}

	Skill::~Skill()
	{
		for (auto kirby : mKirbySkills)
		{
			delete kirby;
		}
	}

	void Skill::Initialize()
	{
		mKirbySkills.resize((UINT)eTransformType::END);

		mKirbySkills[(UINT)eTransformType::DEFAULT] = new DefaultSkill(this);
		mKirbySkills[(UINT)eTransformType::DEFAULT]->SetName(L"DefaultSkill");
		mKirbySkills[(UINT)eTransformType::FIRE] = new FireSkill(this);
		mKirbySkills[(UINT)eTransformType::FIRE]->SetName(L"FireSkill");
		mKirbySkills[(UINT)eTransformType::ICE] = new IceSkill(this);
		mKirbySkills[(UINT)eTransformType::ICE]->SetName(L"IceSkill");


		for (UINT i = 0; i < (UINT)eTransformType::END; i++)
		{
			mKirbySkills[i]->Initialize();
		}

		SetScale(Vector2(20, 18));
	}

	void Skill::Update()
	{
		SetPos(kirby->GetPos());
		type = kirby->GetType();
		mDir = kirby->mDir;

		mKirbySkills[type]->Update();
	}

	void Skill::Render(HDC hdc)
	{
		mKirbySkills[type]->Render(hdc);
	}

	/*void Skill::Release()
	{
		
	}*/
}
