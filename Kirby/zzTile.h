#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Tile : public GameObject
	{
	public:
		Tile();
		virtual ~Tile();

	public:
		virtual void Render(HDC hdc);

	private:

	};
}

