#pragma once

#include "zzGameObject.h"


namespace zz
{
	class Kirby : public GameObject
	{
	public:
		Kirby();
		virtual ~Kirby();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	public:
		int GetType() { return temp; }
		int GetDir() { return mDir; }
		void SetDir(int dir) { mDir = dir; }

	private:
		eTransformType	type;
		int temp;
		int prevTemp;
		int mDir;
		std::vector<GameObject*> mKirbyTransforms;
	};	
}

