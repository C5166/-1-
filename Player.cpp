// =============================
// Gameplay/Actors/Player.cpp
// =============================
#include "Player.h"
#include <algorithm>
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "Consts.h"
#include "AnimationUtil.h"
#include "GameContext.h"
#include "MathUtils.h"

void Player::Init()
{
    sprite = RM().GridAt(ResourceKeys::Player, 1, 2);

    AnimationUtil::BuildWalk(animLeft,  3, RM(), ResourceKeys::Player, 8);
    AnimationUtil::BuildWalk(animRight, 1, RM(), ResourceKeys::Player, 8);
    AnimationUtil::BuildWalk(animUp,    0, RM(), ResourceKeys::Player, 8);
    AnimationUtil::BuildWalk(animDown,  2, RM(), ResourceKeys::Player, 8);

    currentAnim = &animDown;
}

void Player::Reset()
{
    position = { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.9f };
    velocity = {};

    if (currentAnim) currentAnim->Reset();
}

#define BOOLSTR(b) ((b) ? L"true" : L"false")

void Player::Update()
{
    using namespace DxPlus::Input;
    int button = GetButton(PLAYER1);

    bool left   = (button & BUTTON_LEFT) != 0;
    bool right  = (button & BUTTON_RIGHT) != 0;

    // キャラクターが動く方向
    float moveDir = { 0.0f };
    if (left ^ right) moveDir = left ? -1.0f : 1.0f;
    DxPlus::Debug::SetFormatString(L"moveDir : %g", moveDir);

    // キャラクターが目指す速度
    float targetSpeed = moveDir * Const::PLAYER_MAX_SPEED;
    DxPlus::Debug::SetFormatString(L"targetSpeed : %g", targetSpeed);

    // 急ブレーキ中か
    bool isBraking{ false };
    if (std::abs(velocity.x) > Const::EPS &&
        moveDir != 0.0f &&
        velocity.x * targetSpeed < 0.0f)
    {
        isBraking = true;
    }
    DxPlus::Debug::SetFormatString(L"isBraking : %s", BOOLSTR(isBraking));

    //  1フレームで現在の速度をどれだけ目標速度に近づけるか
    float step{ 0.0f };
    if (moveDir != 0.0f)
    {
        step = (isBraking) ? Const::PLAYER_BLAKE : Const::PLAYER_ACCELERATION;
    }
    else
    {
        step = Const::PLAYER_DECELERATION;
    }
    DxPlus::Debug::SetFormatString(L"step : %g", step);

    // 目標速度に近づける
    velocity.x = MathUtils::Approach(velocity.x, targetSpeed, step);
    //if (velocity.x < targetSpeed)
    //{
    //    velocity.x += step;
    //    if (velocity.x > targetSpeed)
    //        velocity.x = targetSpeed;
    //}
    //if (velocity.x > targetSpeed)
    //{
    //    velocity.x -= step;
    //    if (velocity.x < targetSpeed)
    //        velocity.x = targetSpeed;
    //}
    //if (velocity.x < targetSpeed) velocity.x = std::min(velocity.x + step, targetSpeed);
    //if (velocity.x > targetSpeed) velocity.x = std::max(velocity.x - step, targetSpeed);

    // ↓ これはやりすぎで、わかりにくいはず
    //velocity.x = (velocity.x < targetSpeed) ?
    //    std::min(velocity.x + step, targetSpeed) :
    //    std::max(velocity.x - step, targetSpeed);

    //if (velocity.x < -Const::PLAYER_MAX_SPEED)
    //    velocity.x = -Const::PLAYER_MAX_SPEED;
    //if (velocity.x > Const::PLAYER_MAX_SPEED)
    //    velocity.x = Const::PLAYER_MAX_SPEED;

    // プレイヤーの速度を制限
    velocity.x = std::clamp(velocity.x, -Const::PLAYER_MAX_SPEED, Const::PLAYER_MAX_SPEED);
    DxPlus::Debug::SetFormatString(L"velocity.x : %g", velocity.x);

    // プレイヤーのジャンプ入力処理
    jumpPressed = GetButtonDown(PLAYER1) & BUTTON_TRIGGER1;
    jumpHeld = (button & BUTTON_TRIGGER1);

    // アニメーション
    AnimationClip* nextAnim{ nullptr };
    if (velocity.x > 0.0f) nextAnim = &animRight;
    if (velocity.x < 0.0f) nextAnim = &animLeft;
    if (nextAnim && (currentAnim != nextAnim))
    {
        currentAnim = nextAnim;
        currentAnim->Reset();
    }

    if (currentAnim)
    {
        currentAnim->Update();
    }
}

void Player::Step()
{
    // ジャンプ開始処理
    if (isGrounded && jumpPressed)
    {
        velocity.y = -Const::JUMP_SPEED;
        isGrounded = false;
        jumpPressed = false;
    }

    // ジャンプ中にボタンを離したら上昇を早く止める
    if (velocity.y < 0.0f && !jumpHeld)
    {
        velocity.y *= Const::JUMP_CUT_FACTOR;
    }

    // 重力を加えて落下速度を更新する
    velocity.y = std::min(velocity.y + Const::GRAVITY, Const::TERMINAL_VELOCITY);

    Entity2D::Step();

    const float groundY = DxPlus::CLIENT_HEIGHT * 0.9f;
    if (position.y > groundY)
    {
        position.y = groundY;
        velocity.y = 0.0f;
        isGrounded = true;
    }
    else
    {
        isGrounded = false;
    }
    DxPlus::Debug::SetFormatString(L"velocity.y : %g", velocity.y);
    DxPlus::Debug::SetFormatString(L"isGrounded : %s", BOOLSTR(isGrounded));
}
