#include "zzTransformEffect.h"
#include "zzKey.h"


namespace zz
{
	TransformEffect::TransformEffect()
		: mAni(nullptr)
		, obj(nullptr)
	{

	}
	TransformEffect::~TransformEffect()
	{

	}

	void TransformEffect::Initialize()
	{
		mAni = AddComponent<Animator>();

		Texture* TransformEffect = ResourceMgr::Load<Texture>(L"TransformEffect", L"..\\Resources\\TransformEffect.bmp");

		mAni->CreateAnimation(TransformEffect, L"TransformEffect", Vector2(0.f, 0.f), Vector2(81.714f, 59.f), Vector2(81.714f, 0.f), 0.1f, 7);
	}

	void TransformEffect::Update()
	{
		SetPos(Vector2(obj->GetPos().x, obj->GetPos().y + 10.f));
		SetScale(Vector2(81.714f, 59.f));

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