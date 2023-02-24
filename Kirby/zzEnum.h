#pragma once


enum class eSceneType
{
	TITLE,
	PLAY,
	PAUSE,
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