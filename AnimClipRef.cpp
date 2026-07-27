#include "AnimClipRef.h"

void AnimClipRef::AddFrame(const DxPlus::Sprite::SpriteBase* sp, int ticks)
{
    if (!sp) return;
    FrameRef f{ sp, ticks < 1 ? 1 : ticks };
    frames.push_back(f);
}

void AnimClipRef::SetAllDurations(int ticks)
{
    if (ticks < 1) ticks = 1;
    for (auto& f : frames) f.duration = ticks;
}

void AnimClipRef::Update()
{
    if (frames.empty() || !frames[frame].sprite) return;
    if (++counter >= frames[frame].duration)
    {
        counter = 0;
        frame = (frame + 1) % static_cast<int>(frames.size());
    }
}

void AnimClipRef::Reset()
{
    frame = 0, counter = 0;
}

void AnimClipRef::Draw(const DxPlus::Vec2& pos, const DxPlus::Vec2& scale) const
{
    if (frames.empty() || !frames[frame].sprite) return;
    frames[frame].sprite->Draw(pos, scale);
}
