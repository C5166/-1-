// =============================
// Core/GameContext.h
// =============================
#pragma once
#include "DxPlus/DxPlus.h"
#include <memory>
#include <vector>
#include "Projectile.h"

// ゲーム全体で共有する"文脈（コンテキスト）"。
// プレイヤー・敵・マップ・アイテムなどを束ね、
// シーン（Title / Game / Result）から参照できるようにする。
class Entity2D;
class Player;
class GameContext
{
public:
    GameContext() = default;
    ~GameContext() = default;

    // 一度だけ呼ぶ初期化（リソースロードは ResourceManager 側で行う）
    void Init();

    // ステージ再開・リトライ用の軽量リセット
    void Reset();

    // プレイの更新と描画（必要なシーンで呼ぶ）
    void Update();
    void Draw() const;

    void SpawnProjectile(const DxPlus::Vec2& pos, const DxPlus::Vec2& vel) noexcept;
    void SpawnEntity(std::unique_ptr<Entity2D> e) noexcept;

private:
    const DxPlus::Sprite::SpriteBase* backgroundSpr{ nullptr };
    std::vector<std::unique_ptr<Entity2D>> entities;
    std::vector<std::unique_ptr<Projectile>> projectiles;
    std::vector<std::unique_ptr<Entity2D>> spawnQueue;
    Player* player;
};
