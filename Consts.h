// =============================
// Core/Consts.h
// =============================
#pragma once
#include "DxPlus/DxPlus.h"

namespace Const
{
    // ===== プレイヤー関連 =====
    constexpr float PLAYER_SPEED = 4.0f;
    constexpr int MAX_PROJECTILES = 100;
    constexpr DxPlus::Vec2 PLAYER_CENTER_OFFSET = { 0.0f, -48.0f };
    constexpr float PROJECTILE_SPEED = 12.0f;
    constexpr float PROJECTILE_SPAWN_OFFSET = 32.0f;
    constexpr int SHOOT_INTERVAL = 3;

    constexpr float PLAYER_MAX_SPEED = 8.0f;
    constexpr float PLAYER_BLAKE = 0.6f;
    constexpr float PLAYER_ACCELERATION = 0.3f;
    constexpr float PLAYER_DECELERATION = 0.4f;

    // ===== 敵関連 =====
    constexpr float ENEMY_SPEED = 4.0f;
    constexpr float MOVE_DISTANCE = 100.0f;

    // ===== 物理共通 =====
    constexpr float GRAVITY = 1.0f;
    constexpr float TERMINAL_VELOCITY = 16.0f;

    // ===== ジャンプ関連 =====
    constexpr float JUMP_SPEED = 24.0f;
    constexpr float JUMP_CUT_FACTOR = 0.9f;

    // ===== ゲーム内共通 =====
    constexpr float EPS = 1e-3f;
}
