// =============================
// Scenes/Title/TitleScene.h
// =============================
#pragma once
#include "Scene.h"
#include "GameContext.h"

class TitleScene final : public Scene
{
public:
    explicit TitleScene(GameContext* context) : Scene(context) {}
    void Init() override;
    void Update() override;
    void Render() const override;

private:
    int frameCount{ 0 };
    int fontHandle{ -1 };
};
