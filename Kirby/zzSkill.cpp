#include "zzSkill.h"
#include "zzFireSkill.h"
#include "zzDefaultSkill.h"
#include "zzIceSkill.h"
#include "zzCutterSkill.h"

#include "zzSceneMgr.h"

namespace zz
{
	Skill::Skill()
		: type(0)
		, mDir(1)
		, kirby(nullptr)
	{
	}

	Skill::~Skill()
	{
		SceneMgr::GetPlayScene()->ChangeGameObject(mKirbySkills[type], nullptr, eLayerType::SKILL);

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
		mKirbySkills[(UINT)eTransformType::CUTTER] = new CutterSkill(this);
		mKirbySkills[(UINT)eTransformType::CUTTER]->SetName(L"CutterSkill");


		for (UINT i = 0; i < (UINT)eTransformType::END; i++)
		{
			mKirbySkills[i]->Initialize();
			mKirbySkills[i]->SetLayerType(eLayerType::SKILL);
		}

		SetScale(Vector2(20, 18));

		SceneMgr::GetPlayScene()->AddGameObject(mKirbySkills[(UINT)eTransformType::DEFAULT], eLayerType::SKILL);
	}

	void Skill::Update()
	{
		SetPos(kirby->GetPos());

		if (type != kirby->GetType())
		{
			SceneMgr::GetCurScene()->ChangeGameObject(mKirbySkills[type], mKirbySkills[kirby->GetType()], eLayerType::SKILL);
			type = kirby->GetType();
		}
		
		mDir = kirby->GetDir();

		//mKirbySkills[type]->Update();
	}

	void Skill::Render(HDC hdc)
	{
		//mKirbySkills[type]->Render(hdc);
	}

	/*void Skill::Release()
	{
		
	}*/
}
