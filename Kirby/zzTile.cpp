#include "zzTile.h"
#include "zzCamera.h"

namespace zz
{
	Tile::Tile()
	{
		SetScale(TILE_SIZE);
	}

	Tile::~Tile()
	{

	}

	void Tile::Render(HDC hdc)
	{
		Vector2 pos = Camera::GetRenderPos(GetPos());
		Vector2 Scale = GetScale();

		Rectangle(hdc, (int)pos.x, (int)pos.y, (int)(pos.x + Scale.x), (int)(pos.y + Scale.y));


	}
}