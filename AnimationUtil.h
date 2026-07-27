// =============================
// Gameplay/Base/AnimationUtil.h
// =============================
#pragma once
#include "AnimationClip.h"
#include <string>
#include "ResourceManager.h"

namespace AnimationUtil
{
    void BuildWalk(AnimationClip& clip, int y, ResourceManager& rm, const std::wstring& key, int ticks);
}
