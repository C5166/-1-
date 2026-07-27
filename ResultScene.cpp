// =============================
// Scenes/Result/ResultScene.cpp
// =============================
#include "ResultScene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"

void ResultScene::Init()
{
    DxLib::SetBackgroundColor(128, 64, 0);
    fontHandle = RM().GetFont(ResourceKeys::Font_Title);
    StartFadeIn(0.0f);
}

void ResultScene::Update()
{
    using namespace DxPlus::Input;
    if (GetButtonDown(PLAYER1) & BUTTON_START)
    {
        Scene* titleScene = SceneManager::GetInstance().GetScene(SceneID::Title);
        SetNextScene(titleScene);
        StartFadeOut();
        return;
    }
}

void ResultScene::Render() const
{
    gameContext->Draw();

    const int white = DxLib::GetColor(255, 255, 255);
    DxPlus::Text::DrawString(L"Result",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.25f },
        white, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2, 2 }, 0, fontHandle);
}
