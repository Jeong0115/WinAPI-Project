#pragma once

#include "CommonInclude.h"

struct Vector2
{
	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{}

	Vector2(float x, float y)
		: x(x)
		, y(y)
	{}

	/*Vector2(int x, int y)
		: x(x)
		, y(y)
	{}*/

	/*Vector2(const Vector2& other)
		: x(other.x)
		, y(other.y)
	{}

	Vector2(Vector2& other)
		: x(other.x)
		, y(other.y)
	{}*/


	Vector2 (const POINT& pt)
		: x((float)pt.x)
		, y((float)pt.y)
	{}

	Vector2& operator = (POINT pt)
	{
		x = (float)pt.x;
		y = (float)pt.y;
	}

	Vector2 operator+ (Vector2 other)
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator+= (Vector2 other)
	{
		return Vector2(x += other.x, y += other.y);
	}

	Vector2 operator-= (Vector2 other)
	{
		return Vector2(x -= other.x, y -= other.y);
	}

	Vector2 operator- (Vector2 other)
	{
		return Vector2(x - other.x, y - other.y);
	}

	bool operator== (Vector2 other)
	{
		if (x == other.x && y == other.y)
			return true;
		else
			return false;
	}

	Vector2 operator* (int i)
	{
		return Vector2(x * (float)i, y * (float)i);
	}

};