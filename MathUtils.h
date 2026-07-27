// =============================
// Core/MathUtils.h
// =============================
#pragma once
#include <algorithm>

namespace MathUtils
{
    inline float Approach(float current, float target, float step)
    {
        if (current < target) return std::min(current + step, target);
        if (current > target) return std::max(current - step, target);
        return target;
    }
}
