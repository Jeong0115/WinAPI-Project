#include "zzTransformEffect.h"
#include "zzKey.h"


namespace zz
{
	TransformEffect::TransformEffect()
		: mAni(nullptr)
		, mTr(nullptr)
		, obj(nullptr)
	{

	}
	TransformEffect::~TransformEffect()
	{

	}

	void TransformEffect::Initialize()
	{
		mAni = AddComponent<Animator>();
		mTr = AddComponent<Transform>();

		Texture* TransformEffect = ResourceMgr::Load<Texture>(L"TransformEffect", L"..\\Resources\\TransformEffect.bmp");

		mAni->CreateAnimation(TransformEffect, L"TransformEffect", Vector2(0.f, 0.f), Vector2(81.714f, 59.f), Vector2(81.714f, 0.f), 0.1f, 7);
	}

	void TransformEffect::Update()
	{
		mTr->SetPos(obj->GetComponent<Transform>()->GetPos());
		mTr->SetScale(Vector2(81.714f, 59.f));

		mAni->SetPos(mTr->GetPos());
		//mAni->SetPos(Vector2(100.f, 100.f));


		if (KEY(Z, DOWN))
		{
			mAni->PlayAnimation(L"TransformEffect", false);
		}

		GameObject::Update();
	}

	void TransformEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void TransformEffect::Release()
	{
	}
}