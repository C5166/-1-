// =============================
// Resources/ResourceManager.cpp
// =============================
#include "ResourceManager.h"
#include "DxPlus/DxPlus.h"
#include "ResourceKeys.h"

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

void ResourceManager::LoadAll()
{
    LoadTextureAsSpriteLeftTop(ResourceKeys::Background, L"./Data/Images/back.png");
    LoadGridBottom(ResourceKeys::Player, L"./Data/Images/player.png", { 0,0 }, { 3,4 }, { 96,128 });
    LoadGridBottom(ResourceKeys::Enemy_Yankee, L"./Data/Images/yankee.png", { 0,0 }, { 3,4 }, { 96, 128 });
    LoadTextureAsSpriteCenter(ResourceKeys::Player_Shot, L"./Data/Images/player_shot.png");
    LoadGridCenter(ResourceKeys::Explosion, L"./Data/Images/explosion.png", { 0,0 }, { 10,3 }, { 256,256 });

    LoadMusic(ResourceKeys::BGM_Game,       L"./Data/Sounds/maou_bgm_8bit14.mp3");
    LoadSound(ResourceKeys::SE_Explosion,   L"./Data/Sounds/Explosion.mp3");
    LoadSound(ResourceKeys::SE_PlayerShot,  L"./Data/Sounds/PlayerShot.wav");

    LoadFont(ResourceKeys::Font_Title, L"./Data/Fonts/Bitcount/static/Bitcount-Light.ttf");
}

void ResourceManager::UnloadAll()
{
    UnloadGrids();
    UnloadFonts();
}

// ===============================[  GRIDS  ]===================================

const DxPlus::Sprite::SpriteBase* ResourceManager::GridAt(const std::wstring& key, int x, int y)
{
    auto it = grids.find(key);
    if (it == grids.end()) return nullptr;
    const auto& g = it->second;
    if (x < 0 || x >= g.num.x || y < 0 || y >= g.num.y) return nullptr;
    int idx = y * g.num.x + x;
    return &g.frames[idx];
}

void ResourceManager::UnloadGrids()
{
    for (auto& kv : grids) {
        for (auto& f : kv.second.frames) {
            int gid = f.GetID();
            if (gid >= 0) DxPlus::Sprite::Delete(gid);
        }
    }
    grids.clear();
}

int ResourceManager::GetMusic(const std::wstring& key)
{
    auto it = musics.find(key);
    return (it != musics.end()) ? it->second : -1;
}

int ResourceManager::GetSound(const std::wstring& key)
{
    auto it = sounds.find(key);
    return (it != sounds.end()) ? it->second : -1;
}

int ResourceManager::LoadMusic(const std::wstring& key, const std::wstring& path)
{
    int music = DxLib::LoadSoundMem(path.c_str());
    if (music == -1) DxPlus::Utils::FatalError((L"Failed to load music " + path).c_str());
    musics[key] = music;
    return music;
}

int ResourceManager::LoadSound(const std::wstring& key, const std::wstring& path)
{
    int sound = DxLib::LoadSoundMem(path.c_str());
    if (sound == -1) DxPlus::Utils::FatalError((L"Failed to load music " + path).c_str());
    sounds[key] = sound;
    return sound;
}

void ResourceManager::UnloadMusics()
{
    for (auto& m : musics)
    {
        if (m.second >= 0) DxLib::DeleteSoundMem(m.second);
    }
    musics.clear();
}

void ResourceManager::UnloadSounds()
{
    for (auto& s : sounds)
    {
        if (s.second >= 0) DxLib::DeleteSoundMem(s.second);
    }
    sounds.clear();
}

// ===============================[  FONTS  ]===================================

int ResourceManager::GetFont(const std::wstring& fontName)
{
    auto it = fonts.find(fontName);
    if (it == fonts.end())
    {
        DxPlus::Utils::FatalError((L"Font not found: " + fontName).c_str());
    }
    return it->second.handle;
}

int ResourceManager::LoadFont(const std::wstring& fontName, const std::wstring& path)
{
    if (AddFontResourceExW(path.c_str(), FR_PRIVATE, 0) == 0)
    {
        DxPlus::Utils::FatalError((std::wstring(L"Failed to add font: ") + path).c_str());
    }

    int handle = DxPlus::Text::InitializeFont(fontName.c_str(), 40, 2);
    if (handle == -1)
    {
        DxPlus::Utils::FatalError((std::wstring(L"Failed to init font: ") + fontName).c_str());
    }

    fonts[fontName] = { handle, path };

    return handle;
}

void ResourceManager::UnloadFont(const std::wstring& fontName)
{
    auto it = fonts.find(fontName);
    if (it == fonts.end()) return;

    auto& info = it->second;

    if (info.handle != -1)
    {
        DxPlus::Text::DeleteFont(info.handle);
        info.handle = -1;
    }

    if (!info.path.empty())
    {
        RemoveFontResourceExW(info.path.c_str(), FR_PRIVATE, 0);
    }

    fonts.erase(it);
}

void ResourceManager::UnloadFonts()
{
    std::vector<std::wstring> keys;
    keys.reserve(fonts.size());
    for (const auto& pair : fonts)// kv:key-value
    {
        keys.push_back(pair.first);
    }

    for (const auto& name : keys)
    {
        UnloadFont(name);
    }
}
