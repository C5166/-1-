// =============================
// Scenes/Title/TitleScene.cpp
// =============================
#include "TitleScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ResourceKeys.h"

void TitleScene::Init()
{
    DxLib::SetBackgroundColor(16, 128, 224);
    frameCount = 0;

    fontHandle = RM().GetFont(ResourceKeys::Font_Title);

    StartFadeIn();
}

void TitleScene::Update()
{
    using namespace DxPlus::Input;
    if (GetButtonDown(PLAYER1) & BUTTON_START)
    {
        Scene* gameScene = SceneManager::GetInstance().GetScene(SceneID::Game);
        SetNextScene(gameScene);
        StartFadeOut();
        return;
    }
    frameCount++;
}

void TitleScene::Render() const
{
    const int white = DxLib::GetColor(255, 255, 255);
    DxPlus::Text::DrawString(L"2D GameProgramming II", 
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.25f }, 
        white, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 2, 2 }, 0, fontHandle);

    const int yellow = DxLib::GetColor(255, 255, 0);
    if (frameCount & 0x20)
    {
        DxPlus::Text::DrawString(L"Push Enter", 
            { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.75f }, 
            yellow, DxPlus::Text::TextAlign::MIDDLE_CENTER, { 1,1 }, 0, fontHandle);
    }
}
