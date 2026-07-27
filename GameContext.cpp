// =============================
// Core/GameContext.cpp
// =============================
#include "GameContext.h"
#include <algorithm>
#include "Entity2D.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "Player.h"
#include "Consts.h"
#include "Collision2D.h"

void GameContext::Init()
{
    //  DxLib::SetMouseDispFlag(FALSE);
    backgroundSpr = RM().GridAt(ResourceKeys::Background);

}

void GameContext::Reset()
{
    gridManager.Initialize(10, 120, 192.0f, DxPlus::Vec2(0.0f, 0.0f));

    entities.clear();
    entities.emplace_back(std::make_unique<Player>());
    player = static_cast<Player*>(entities.back().get());

    for (auto& e : entities)
    {
        e->BindContext(this);
        e->Init();
        e->Reset();
    }

    projectiles.clear();
    projectiles.reserve(Const::MAX_PROJECTILES);
}

void GameContext::Update()
{
    // ★ GridManager の更新
	gridManager.Update(DxPlus::deltaTime, player->GetPosition().y);

    for (auto& e : entities) e->Update();
    for (auto& p : projectiles) p->Update();

    for (auto& e : entities) e->Step();
    for (auto& p : projectiles) p->Step();

    // 弾と敵のあたり判定（円×円）
    for (auto& p : projectiles)
    {
        if (!p->IsAlive()) continue;

        for (auto& e : entities)
        {
            if (!e->IsAlive() ||
                !e->IsDamageable()) continue;

            if (Collision2D::CircleVsCircle(
                p->GetPosition(), p->Radius(),
                e->GetPosition() + e->GetCenterOffset(), e->Radius()))
            {
                e->OnHit(p->Attack());
                p->Kill();
                break;
            }
        }
    }

    // 存在が消えたEntity2Dをentitiesから削除する
    {
        std::vector<std::unique_ptr<Entity2D>>::iterator it = entities.begin();
        while (it != entities.end())
        {
            if (!(*it)->IsAlive())
            {
                it = entities.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    // 存在が消えたProjectileをprojectilesから削除する
    {
        std::vector<std::unique_ptr<Projectile>>::iterator it = projectiles.begin();
        while (it != projectiles.end())
        {
            if (!(*it)->IsAlive())
            {
                it = projectiles.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    if (!spawnQueue.empty())
    {
        for (auto& s : spawnQueue)
        {
            entities.push_back(std::move(s));
        }
        spawnQueue.clear();
    }

    std::wstring text = std::wstring(L"Player Position(") +
        std::to_wstring(static_cast<int>(player->GetPosition().x)) +
        L"," +
        std::to_wstring(static_cast<int>(player->GetPosition().y)) +
        L")";
    DxPlus::Debug::SetString(text);
}

void GameContext::Draw() const
{
    // 1. 最背面：背景描画
    if (backgroundSpr)
    {
        backgroundSpr->Draw({});
    }

    // 2. 中間：ブロック群の描画（背景とプレイヤーの間に挟む）
	gridManager.Draw(player->GetPosition().y, 1080.0f);

    // 3. 最前面：プレイヤー等のエンティティ描画
    std::vector<Entity2D*> drawList{};
    for (auto& e : entities) drawList.push_back(e.get());
    for (auto& p : projectiles) drawList.push_back(p.get());

    std::sort(drawList.begin(), drawList.end(),
        [](const Entity2D* a, const Entity2D* b)->bool
        {
            return a->GetPosition().y < b->GetPosition().y;
        }
    );
    for (auto& d : drawList)
    {
        d->Draw();
    }
}

void GameContext::SpawnProjectile(const DxPlus::Vec2& pos, const DxPlus::Vec2& vel) noexcept
{
    if (projectiles.size() >= Const::MAX_PROJECTILES) return;
    auto pr = std::make_unique<Projectile>();
    pr->Init();
    pr->Reset(pos, vel);
    projectiles.push_back(std::move(pr));
}

void GameContext::SpawnEntity(std::unique_ptr<Entity2D> e) noexcept
{
    e->BindContext(this);
    e->Init();
    e->Reset();
    spawnQueue.push_back(std::move(e));
}