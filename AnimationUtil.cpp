// =============================
// Gameplay/Base/AnimationUtil.cpp
// =============================
#include "AnimationUtil.h"

namespace AnimationUtil
{
    void BuildWalk(AnimationClip& clip, int y, ResourceManager& rm, const std::wstring& key, int ticks)
    {
        clip.Clear();
        std::vector<int> walkCycle{ 1,0,1,2 };
        for (auto& x : walkCycle) clip.AddFrame(rm.GridAt(key, x, y), ticks);
        clip.Reset();
    }
}
