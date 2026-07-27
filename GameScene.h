// =============================
// Scenes/Game/GameScene.h
// =============================
#pragma once
#include "Scene.h"
#include "GameContext.h"

class GameScene final : public Scene
{
public:
    explicit GameScene(GameContext* context) : Scene(context) {}
    void Init() override;
    void Update() override;
    void Render() const override;
    void End() override;

private:
};
