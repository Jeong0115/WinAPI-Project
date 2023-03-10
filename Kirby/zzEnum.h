#pragma once


enum class eSceneType
{
	FIRST,
	TITLE,
	TOOL,
	PLAY,
	PAUSE,
	ENDING,
	MAX
};

enum class eLayerType
{
	BACKGROUND,
	STAGE,
	TILE,
	INVENTORY,
	ITEM,
	MONSTER,
	PLAYER,
	FOREGROUND,
	SKILL,
	INHALE,
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

enum class eEventType
{
	CREATE_OBJ,
	DELETE_OBJ,
	CHANGE_OBJ,
	SCENE_CHANGE,
	END
};

enum class eAbillityType
{
	DEFAULT,
	FIRE,
	ICE,
	CUTTER,
	END
};

enum class eState
{
	ACTIVE,
	INVINCIBLE,
	CHANGE,
	INHALE,
	DEAD
};
