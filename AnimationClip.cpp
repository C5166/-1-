// =============================
// Gameplay/Base/AnimationClip.cpp
// =============================
#include "AnimationClip.h"

void AnimationClip::AddFrame(const DxPlus::Sprite::SpriteBase* sp, int ticks)
{
    if (!sp) return;
    frames.push_back({ sp, ticks < 1 ? 1 : ticks });
}

void AnimationClip::SetAllDurations(int ticks)
{
    for (auto& f : frames)
    {
        f.duration = ticks < 1 ? 1 : ticks;
    }
}

void AnimationClip::Clear()
{
    frames.clear();
    frame = 0;
    counter = 0;
}

void AnimationClip::Reset()
{
    frame = 0;
    counter = 0;
}

void AnimationClip::Update()
{
    if (frames.empty() || !frames[frame].sprite) return;
    if (++counter >= frames[frame].duration)
    {
        counter = 0;
        frame = (frame + 1) % static_cast<int>(frames.size());
    }
}

void AnimationClip::Draw(const DxPlus::Vec2& pos, const DxPlus::Vec2& scale) const
{
    if (frames.empty() || !frames[frame].sprite) return;
    frames[frame].sprite->Draw(pos, scale);
}
