// =============================
// Scenes/Base/SceneManager.cpp
// =============================
#include "SceneManager.h"
#include "ResourceManager.h"
#include "DxPlus/DxPlus.h"

void SceneManager::Init()
{
    constexpr bool WINDOWED = true;
    DxPlus::Initialize(DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT, WINDOWED);
    ResourceManager::GetInstance().LoadAll();
    gameContext.Init();

    titleScene.SetGameContext(&gameContext);
    gameScene.SetGameContext(&gameContext);
    resultScene.SetGameContext(&gameContext);

    scene = &titleScene; // 最初のシーン
}

void SceneManager::Shutdown()
{
    ResourceManager::GetInstance().UnloadAll();
    DxPlus::Shutdown();
}

void SceneManager::SetScene(Scene* newScene)
{
    if (!newScene || newScene == scene) return;
    scene = newScene; // 破棄しない＝常駐
}

Scene* SceneManager::GetScene(SceneID id)
{
    switch (id)
    {
        case SceneID::Title:    return &titleScene;
        case SceneID::Game:     return &gameScene;
        case SceneID::Result:   return &resultScene;
    }
    return &titleScene;
}

void SceneManager::Run()
{
    if (scene) scene->Init();
    while (DxPlus::GameLoop())
    {
        DxPlus::Input::Update();
        if (scene)
        {
            DxLib::ClearDrawScreen();

            DxPlus::Debug::SetString(L"08_Sample");
            DxPlus::Debug::SetString(L"A、Dで左右移動、スペースでジャンプ");
            DxPlus::Debug::SetString(L"");
            scene->Drive();
            scene->Render();

            if (scene->IsFinished())
            {
                scene->End();

                Scene* next = scene->GetNextScene();
                scene->SetNextScene(nullptr);   // 元のシーンのnextSceneをnullptr、finishedをfalseに設定している

                if (!next) { DxLib::ScreenFlip(); break; }
                SetScene(next);
                next->Init();
            }
            DxPlus::Debug::Draw();
            scene->DrawFadeOverlay();
            DxLib::ScreenFlip();
        }
    }
}
