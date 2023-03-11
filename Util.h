#pragma once
#include"Vector2.h"

bool CheckHitBoxAndBox(Vector2 pos, Vector2 length, Vector2 pos2, Vector2 length2);

template <class T>
constexpr const T& clamp(const T& v, const T& low, const T& high)
{
	if (v < low) { return low; }
	if (v > high) { return high; }
	return v;
}

