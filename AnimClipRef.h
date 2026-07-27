#pragma once
#include <vector>
#include <string>
#include "DxPlus/Sprite.h"

struct FrameRef
{
    const DxPlus::Sprite::SpriteBase* sprite = nullptr;
    int duration = 8;
};

class AnimClipRef
{
public:
    void Clear() { frames.clear(); frame = 0; counter = 0; }
    void AddFrame(const DxPlus::Sprite::SpriteBase* sp, int ticks);
    void SetAllDurations(int ticks);
    void Update();
    void Reset();
    void Draw(const DxPlus::Vec2& pos, const DxPlus::Vec2& scale = { 1,1 }) const;

private:
    std::vector<FrameRef> frames;
    int frame = 0, counter = 0;
};
