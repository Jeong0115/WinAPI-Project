#pragma once


enum class eSceneType
{
	TITLE,
	PLAY,
	ENDING,
	MAX
};

enum class eLayerType
{
	BACKGROUND,
	ITEM,
	MONSTER,
	PLAYER,
	FOREGROUND,
	EFFECT,
	UI,
	END
};

enum class eCompType
{
	TRANSFORM,
	COLLIDER,
	SPRITERENDER,
	ANIMATOR,
	AUDIO,
	END,
};