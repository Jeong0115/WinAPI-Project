//#include "zzSkill.h"
//#include "zzFireSkill.h"
//#include "zzDefaultSkill.h"
//#include "zzIceSkill.h"
//#include "zzCutterSkill.h"
//
//#include "zzSceneMgr.h"
//
//namespace zz
//{
//	Skill::Skill(Player* kirby)
//		: mType(0)
//		, mDir(1)
//		, mKirby(kirby)
//	{
//	}
//
//	Skill::~Skill()
//	{
//		SceneMgr::GetPlayScene()->ChangeGameObject(mKirbySkills[mType], nullptr, eLayerType::SKILL);
//
//		for (auto kirby : mKirbySkills)
//		{
//			delete kirby;
//		}
//	}
//
//	void Skill::Initialize()
//	{
//		mKirbySkills.resize(2);
//
//		mKirbySkills[(UINT)eAbillityType::DEFAULT] = new DefaultSkill(this);
//		mKirbySkills[(UINT)eAbillityType::DEFAULT]->SetName(L"DefaultSkill");
//		mKirbySkills[(UINT)eAbillityType::FIRE] = new FireSkill(this);
//		mKirbySkills[(UINT)eAbillityType::FIRE]->SetName(L"FireSkill");
//		mKirbySkills[(UINT)eAbillityType::ICE] = new IceSkill(this);
//		mKirbySkills[(UINT)eAbillityType::ICE]->SetName(L"IceSkill");
//
//
//
//		for (UINT i = 0; i < 2; i++)
//		{
//			mKirbySkills[i]->Initialize();
//			mKirbySkills[i]->SetLayerType(eLayerType::SKILL);
//		}
//
//		SetScale(Vector2(20, 18));
//
//		SceneMgr::GetPlayScene()->AddGameObject(mKirbySkills[(UINT)eAbillityType::DEFAULT], eLayerType::SKILL);
//	}
//
//	void Skill::Update()
//	{
//		SetPos(mKirby->GetPos());
//
//		if (mType != mKirby->GetType())
//		{
//			SceneMgr::GetCurScene()->ChangeGameObject(mKirbySkills[mType], mKirbySkills[mKirby->GetType()], eLayerType::SKILL);
//			mType = mKirby->GetType();
//		}
//		
//		mDir = mKirby->GetDir();
//
//		//mKirbySkills[mType]->Update();
//	}
//
//	void Skill::Render(HDC hdc)
//	{
//		//mKirbySkills[mType]->Render(hdc);
//	}
//
//	/*void Skill::Release()
//	{
//		
//	}*/
//}
