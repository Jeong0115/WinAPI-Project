#include "zzCollisionMgr.h"
#include "zzSceneMgr.h"
#include "zzLayer.h"
#include "zzApplication.h"
#include "zzSelectGDI.h"

namespace zz
{
	UINT CollisionMgr::mCheck[(UINT)eLayerType::END] = {};

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
		Scene* nowScene = SceneMgr::GetNowScene();

		Layer* leftLayer = nowScene->GetLayer((eLayerType)left);
		Layer* rightLayer = nowScene->GetLayer((eLayerType)right);

		const std::vector<GameObject*>& vecLeft = leftLayer->GetGameObjects();
		const std::vector<GameObject*>& vecRight = rightLayer->GetGameObjects();

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

				if (IsCollision(vecLeft[i]->GetComponent<Collider>()
					, vecRight[i]->GetComponent<Collider>()))
				{
					Application::SetPen(Application::GetRedPen());
				}
				else
				{
					Application::SetPen(Application::GetGreenPen());
				}
			}
		}
	}

	bool CollisionMgr::IsCollision(Collider* left, Collider* right)
	{
		RECT rect;
		RECT leftRect = {
			left->GetPos().x - left->GetScale().x / 2.f, left->GetPos().y - left->GetScale().y / 2.f
			, left->GetPos().x + left->GetScale().x / 2.f, left->GetPos().y + left->GetScale().y / 2.f
		};
		RECT rightRect = {
			right->GetPos().x - right->GetScale().x / 2.f, right->GetPos().y - right->GetScale().y / 2.f
			, right->GetPos().x + right->GetScale().x / 2.f, right->GetPos().y + right->GetScale().y / 2.f
		};


		if (IntersectRect(&rect, &leftRect, &rightRect))
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