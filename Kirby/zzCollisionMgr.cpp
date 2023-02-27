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
		Scene* nowScene = SceneMgr::GetCurScene();

		Layer* leftLayer = nowScene->GetLayer((eLayerType)left);
		Layer* rightLayer = nowScene->GetLayer((eLayerType)right);

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
				ID.rightID = vecRight[i]->GetComponent<Collider>()->GetID();

				iter = mCollisionMap.find(ID.ID);

				if (iter == mCollisionMap.end())
				{
					mCollisionMap.insert(std::make_pair(ID.ID, false));
					iter = mCollisionMap.find(ID.ID);
				}

				if (IsCollision(vecLeft[i]->GetComponent<Collider>()
					, vecRight[i]->GetComponent<Collider>()))
				{
					if (iter->second)
					{
						vecLeft[i]->GetComponent<Collider>()->OnCollision();
						vecRight[i]->GetComponent<Collider>()->OnCollision();
					}
					else
					{
						vecLeft[i]->GetComponent<Collider>()->OnCollisionEnter();
						vecRight[i]->GetComponent<Collider>()->OnCollisionEnter();
					}
					//vecRight[j]->GetComponent<Collider>()->GetPen() = Application::GetRedPen();
					//vecLeft[j]->GetComponent<Collider>()->GetPen() = Application::GetRedPen();
					//Application::SetPen(Application::GetRedPen());

					iter->second = true;
				}
				else
				{
					if (iter->second)
					{
						vecLeft[i]->GetComponent<Collider>()->OnCollisionExit();
						vecRight[i]->GetComponent<Collider>()->OnCollisionExit();
					}
					//vecLeft[i]->GetComponent<Collider>()->GetPen() = Application::GetGreenPen();
					//vecRight[i]->GetComponent<Collider>()->GetPen() = Application::GetGreenPen();
					//Application::SetPen(Application::GetGreenPen());

					iter->second = false;
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

		if (abs(left->GetPos().x - right->GetPos().x) < (left->GetScale().x + right->GetScale().x) / 2.f
			&& abs(left->GetPos().y - right->GetPos().y) < (left->GetScale().y + right->GetScale().y) / 2.f)
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