#include "zzMonster.h"
#include "zzTime.h"


namespace zz
{
	Monster::Monster()
		: mSpeed(70.f)
		, mCenterPos{ Vector2(0.f,0.f) }
		, mMaxDistance(100.f)
		, mDir(1)
		, mbHit(false)
		, mColli(nullptr)
		, mAni(nullptr)
		, mHitTime(0.f)
		, mDeadTime(0.f)
		, mbCadaver(false)
		, mHp(5)
	{
	}

	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* KingDedede_Right = ResourceMgr::Load<Texture>(L"KingDedede_Right", L"..\\Resources\\KingDedede_Right.bmp");
		Texture* KingDedede_Left = ResourceMgr::Load<Texture>(L"KingDedede_Left", L"..\\Resources\\KingDedede_Left.bmp");

		mAni->CreateAnimation(KingDedede_Right, L"KingDedede_Right_Hit", Vector2(638.f, 386.f), Vector2(62.f, 67.f), Vector2(-62.f, 0.f), 0.05f, 1);
		mAni->CreateAnimation(KingDedede_Left, L"KingDedede_Left_Hit", Vector2(20.f, 386.f), Vector2(62.f, 67.f), Vector2(62.f, 0.f), 0.05f, 1);

		mAni->CreateAnimation(KingDedede_Left, L"KingDedede_Left_Walk", Vector2(321.f, 5.f), Vector2(63.f, 61.f), Vector2(63.f, 0.f), 0.2f, 4);
		mAni->CreateAnimation(KingDedede_Right, L"KingDedede_Right_Walk", Vector2(336.f, 5.f), Vector2(63.f, 61.f), Vector2(-63.f, 0.f), 0.2f, 4);

		mAni->CreateAnimation(KingDedede_Left, L"KingDedede_Left_Dead", Vector2(109.f, 388.f), Vector2(64.f, 58.f), Vector2(64.f, 0.f), 1.f, 3);
		mAni->CreateAnimation(KingDedede_Right, L"KingDedede_Right_Dead", Vector2(547.f, 388.f), Vector2(64.f, 58.f), Vector2(-64.f, 0.f), 1.f, 3);


		SetPos(Vector2( 700.f, 150.f ));
		SetScale(Vector2(62.f, 55.f));



		SetCenterPos(Vector2(GetPos().x +50, GetPos().y));

		GameObject::Initialize();
	}

	void Monster::Update()
	{

		if (mbCadaver)
		{
			mDeadTime += (float)Time::DeltaTime();

			if (mDeadTime >= 5.f)
			{
				DeleteObject(this, GetLayerType());
			}
		}
		else
		{
			if (!mbHit)
			{
				Vector2 curPos = GetPos();

				curPos.x += (float)Time::DeltaTime() * mSpeed * mDir;

				float dist = abs(mCenterPos.x - curPos.x) - mMaxDistance;

				if (0.f < dist)
				{
					mDir *= -1;
					curPos.x += dist * mDir;
					if (mDir > 0)
					{
						mAni->PlayAnimation(L"KingDedede_Right_Walk", true);
					}
					else
					{
						mAni->PlayAnimation(L"KingDedede_Left_Walk", true);
					}
				}

				SetPos(curPos);
			}
			else
			{
				mHitTime += (float)Time::DeltaTime();

				if (mHitTime >= 1.f)
				{
					mbHit = false;
					mHitTime = 0.f;
					if (mDir == 1)
					{
						mAni->PlayAnimation(L"KingDedede_Right_Walk", true);
					}
					else
					{
						mAni->PlayAnimation(L"KingDedede_Left_Walk", true);
					}
				}
			}
		}
		GameObject::Update();
	}

	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Monster::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == (eLayerType::SKILL))
		{
			if (mDir == 1)
			{
				mAni->PlayAnimation(L"KingDedede_Right_Hit", true);
			}
			else
			{
				mAni->PlayAnimation(L"KingDedede_Left_Hit", true);
			}
			mbHit = true;
			mHp--;
		}

		if (mHp <= 0)
		{
			mbCadaver = true;
			SetScale(Vector2(0.f, 0.f));
			//delete mColli;
			if (mDir == 1)
			{
				mAni->PlayAnimation(L"KingDedede_Right_Dead", true);
			}
			else
			{
				mAni->PlayAnimation(L"KingDedede_Left_Dead", true);
			}
		}
	}

	void Monster::OnCollision(GameObject* other)
	{
	}

	void Monster::OnCollisionExit(GameObject* other)
	{
	}
}
