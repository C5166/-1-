// =============================
// Gameplay/Base/Collision2D.h
// =============================
#pragma once
#include "DxPlus/DxPlus.h"

namespace Collision2D
{
	inline bool CircleVsCircle(
		const DxPlus::Vec2& a, float ra,
		const DxPlus::Vec2& b, float rb)
	{
		float x = a.x - b.x;
		float y = a.y - b.y;
		float rr = (ra + rb) * (ra + rb);
		return x * x + y * y < rr;
	}
}
