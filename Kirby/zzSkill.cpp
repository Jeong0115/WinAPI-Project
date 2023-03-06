#include "zzSkill.h"
#include "zzFireSkill.h"
#include "zzDefaultSkill.h"
#include "zzIceSkill.h"
#include "zzCutterSkill.h"

#include "zzSceneMgr.h"

namespace zz
{
	Skill::Skill(Kirby* kirby)
		: mType(0)
		, mDir(1)
		, mKirby(kirby)
	{
	}

	Skill::~Skill()
	{
		SceneMgr::GetPlayScene()->ChangeGameObject(mKirbySkills[mType], nullptr, eLayerType::SKILL);

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
		SetPos(mKirby->GetPos());

		if (mType != mKirby->GetType())
		{
			SceneMgr::GetCurScene()->ChangeGameObject(mKirbySkills[mType], mKirbySkills[mKirby->GetType()], eLayerType::SKILL);
			mType = mKirby->GetType();
		}
		
		mDir = mKirby->GetDir();

		//mKirbySkills[mType]->Update();
	}

	void Skill::Render(HDC hdc)
	{
		//mKirbySkills[mType]->Render(hdc);
	}

	/*void Skill::Release()
	{
		
	}*/
}
