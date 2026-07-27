// =============================
// Gameplay/Base/AnimationClip.h
// =============================
#pragma once
#include <vector>
#include "DxPlus/DxPlus.h"

class AnimationClip
{
public:
    AnimationClip() = default;
    void AddFrame(const DxPlus::Sprite::SpriteBase* sp, int ticks);
    void SetAllDurations(int ticks);
    void Clear();
    void Reset();
    void Update();
    void Draw(const DxPlus::Vec2& pos, const DxPlus::Vec2& scale = { 1,1 }) const;
private:
    struct AnimationFrame
    {
        const DxPlus::Sprite::SpriteBase* sprite{ nullptr };
        int duration{ 0 };
    };
    std::vector<AnimationFrame> frames{};
    int frame{ 0 };
    int counter{ 0 };
};
