#include "zzCollisionMgr.h"
#include "zzSceneMgr.h"
#include "zzLayer.h"
#include "zzApplication.h"
#include "zzSelectGDI.h"

namespace zz
{
	UINT CollisionMgr::mCheck[(UINT)eLayerType::END] = {};
	std::map<ULONGLONG, bool> CollisionMgr::mCollisionMap = {};

	CollisionMgr::CollisionMgr()
	{
	}

	CollisionMgr::~CollisionMgr()
	{
	}

	void CollisionMgr::Initialize()
	{
	}

	void CollisionMgr::Update()
	{
		for (UINT row = 0; row < (UINT)eLayerType::END; row++)
		{	
			for (UINT col = row; col < (UINT)eLayerType::END; col++)
			{
				if (mCheck[row] & (1 << col)) 
				{
					Update2((eLayerType)row, (eLayerType)col);
				}
			}
		}
	}

	void CollisionMgr::Update2(eLayerType left, eLayerType right)
	{
		Scene* curScene = SceneMgr::GetCurScene();

		Layer* leftLayer = curScene->GetLayer((eLayerType)left);
		Layer* rightLayer = curScene->GetLayer((eLayerType)right);

		if (leftLayer == nullptr || rightLayer == nullptr)
			return;


		const std::vector<GameObject*>& vecLeft = leftLayer->GetGameObjects();
		const std::vector<GameObject*>& vecRight = rightLayer->GetGameObjects();
		std::map<ULONGLONG, bool>::iterator iter;

		for (UINT i = 0; i < vecLeft.size(); i++)
		{
			if (nullptr == vecLeft[i]->GetComponent<Collider>())
			{
				continue;
			}

			for (UINT j = 0; j < vecRight.size(); j++)
			{
				if (nullptr == (vecRight[j]->GetComponent<Collider>())
					|| vecLeft[i] == vecRight[j])
				{
					continue;
				}

				COLLIDER_ID ID;

				ID.leftID = vecLeft[i]->GetComponent<Collider>()->GetID();
				ID.rightID = vecRight[j]->GetComponent<Collider>()->GetID();

				iter = mCollisionMap.find(ID.ID);

				if (iter == mCollisionMap.end())
				{
					mCollisionMap.insert(std::make_pair(ID.ID, false));
					iter = mCollisionMap.find(ID.ID);
				}

				if (IsCollision(vecLeft[i]->GetComponent<Collider>()
					, vecRight[j]->GetComponent<Collider>()))
				{
					if (iter->second)
					{
						if (vecLeft[i]->IsDead() || vecRight[i]->IsDead())
						{
							vecLeft[i]->GetComponent<Collider>()->OnCollisionExit(vecRight[j]);
							vecRight[j]->GetComponent<Collider>()->OnCollisionExit(vecLeft[i]);
							iter->second = false;
						}
						else
						{
							vecLeft[i]->GetComponent<Collider>()->OnCollision(vecRight[j]);
							vecRight[j]->GetComponent<Collider>()->OnCollision(vecLeft[i]);
							iter->second = true;
						}
					}
					else
					{
						if (!vecLeft[i]->IsDead() || !vecRight[i]->IsDead())
						{
							vecLeft[i]->GetComponent<Collider>()->OnCollisionEnter(vecRight[j]);
							vecRight[j]->GetComponent<Collider>()->OnCollisionEnter(vecLeft[i]);
							iter->second = true;
						}
					}
				}

				else
				{
					if (iter->second)
					{
						vecLeft[i]->GetComponent<Collider>()->OnCollisionExit(vecRight[j]);
						vecRight[j]->GetComponent<Collider>()->OnCollisionExit(vecLeft[i]);
						iter->second = false;
					}	
				}
			}
		}
	}

	bool CollisionMgr::IsCollision(Collider* left, Collider* right)
	{
		/*RECT rect;
		RECT leftRect = {
			(LONG)(left->GetPos().x - left->GetScale().x / 2.f), (LONG)(left->GetPos().y - left->GetScale().y / 2.f)
			, (LONG)(left->GetPos().x + left->GetScale().x / 2.f), (LONG)(left->GetPos().y + left->GetScale().y / 2.f)
		};
		RECT rightRect = {
			(LONG)(right->GetPos().x - right->GetScale().x / 2.f), (LONG)(right->GetPos().y - right->GetScale().y / 2.f)
			, (LONG)(right->GetPos().x + right->GetScale().x / 2.f), (LONG)(right->GetPos().y + right->GetScale().y / 2.f)
		};


		if (IntersectRect(&rect, &leftRect, &rightRect))
		{
			return true;
		}*/
		GameObject* leftObj = left->GetOwner();
		GameObject* RightObj = right->GetOwner();

		if (abs(leftObj->GetPos().x - RightObj->GetPos().x) < (leftObj->GetScale().x + RightObj->GetScale().x) / 2.f
			&& abs((leftObj->GetPos().y - leftObj->GetScale().y / 2.f)
				- (RightObj->GetPos().y - RightObj->GetScale().y / 2.f)) < (leftObj->GetScale().y + RightObj->GetScale().y) / 2.f)
		{
			return true;
		}

		return false;
	}

	void CollisionMgr::CheckCollision(eLayerType left, eLayerType right)
	{
		UINT row = (UINT)left;
		UINT col = (UINT)right;

		if (row > col)
		{
			col = (UINT)left;
			row = (UINT)right;
		}

		if (mCheck[row] & (1 << col))
		{
			mCheck[row] &= ~(1 << col);
		}
		else
		{
			mCheck[row] |= (1 << col);
		}	
	}

	void CollisionMgr::ResetCollision()
	{
		memset(mCheck, 0, sizeof((UINT)eLayerType::END));
	}
}