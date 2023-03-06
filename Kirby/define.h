#pragma once


#define KEY(key,state) Key::GetKeyState(eKeyCode::key) == eKeyState::state

#define TILE_SIZE Vector2(8.f,8.f)