// =============================
// Gameplay/Actors/Player.h
// =============================
#pragma once
#include "Entity2D.h"

class Player : public Entity2D
{
public:
    Player() = default;
    ~Player() = default;

    // ライフサイクル処理
    void Init() override;
    void Reset() override;
    void Update() override;
    void Step() override;

private:
    DxPlus::Vec2 prevVelocity{ 0,1 };
    int shootInterval{};
    int rotate{};
    bool jumpPressed{ false };
    bool jumpHeld{ false };
};
