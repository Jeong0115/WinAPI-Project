#pragma once

#include "zzEngine.h"

namespace zz
{
	enum class eKeyCode
	{
		LEFT, RIGHT, UP, DOWN,
		Z, X, Q, P, ENTER, ESC, LAST
	};

	enum class eKeyState
	{
		DOWN,
		PRESSED,
		UP,
		NONE
	};

	class Key
	{
	public:
		struct KeyInfo
		{
			eKeyCode	key;
			eKeyState	state;
			bool		bPressed;
		};

		static void Initialize();
		static void Update();

		inline static eKeyState GetKeyState(eKeyCode keyCode) { return mVecKeyInfo[(UINT)keyCode].state; }

	private:
		static std::vector<KeyInfo> mVecKeyInfo;
	};
}

