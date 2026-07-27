// =============================
// Resources/ResourceManager.h
// =============================
#pragma once
#include <string>
#include <unordered_map>
#include "DxPlus/DxPlus.h"

class ResourceManager
{
public:
    static ResourceManager& GetInstance();

    /// <summary>
    /// ResourceManager が管理する全てのリソースを読み込み、
    /// 使用可能な状態に初期化します。
    /// （フォントやスプライトなど、必要なリソースを一括ロード）
    /// </summary>
    void LoadAll();

    /// <summary>
    /// ResourceManager が管理している全てのリソースを解放します。
    /// （フォント・スプライト・タイルセットなどをまとめて破棄）
    /// </summary>
    void UnloadAll();

    // ===============================[  FONTS  ]===================================
    
    /// <summary>
    /// 指定したフォント名に対応するフォントハンドルを取得します。
    /// </summary>
    /// <param name="fontName">取得対象のフォント名（登録済みである必要あり）</param>
    /// <returns>
    /// フォントハンドル（存在しない場合は -1 を返す）
    /// </returns>
    int GetFont(const std::wstring& fontName);

    // ===============================[  SPRITES(Grid / Single)  ]===================================

    // スプライトシートを分割して登録（詳細は定義部参照）
    template <typename TSprite = DxPlus::Sprite::SpriteBottom>
    int LoadGrid(const std::wstring& key, const std::wstring& path,
        DxPlus::Vec2Int start, DxPlus::Vec2Int num, DxPlus::Vec2Int size);

    // テクスチャをスプライト化して登録
    template <typename TSprite = DxPlus::Sprite::SpriteBottom>
    const DxPlus::Sprite::SpriteBase* LoadTextureAsSprite(
        const std::wstring& key, const std::wstring& path);

    /// <summary>
    /// スプライトシートをグリッド状に分割してロードし、
    /// 各スプライトの左上を原点として登録します。
    /// </summary>
    /// <param name="key">登録用のキー文字列</param>
    /// <param name="path">画像ファイルのパス</param>
    /// <param name="start">分割開始位置（左上座標、ピクセル単位）</param>
    /// <param name="num">分割する枚数（横方向・縦方向のセル数）</param>
    /// <param name="size">1セルあたりのサイズ（幅・高さ）</param>
    /// <returns>ロードして追加されたスプライトの総数</returns>
    int LoadGridLeftTop(const std::wstring& key, const std::wstring& path,
        DxPlus::Vec2Int start, DxPlus::Vec2Int num, DxPlus::Vec2Int size)
    {
        return LoadGrid<DxPlus::Sprite::SpriteLeftTop>(key, path, start, num, size);
    }
    /// <summary>
    /// スプライトシートをグリッド状に分割してロードし、
    /// 各スプライトの中心を原点として登録します。
    /// </summary>
    /// <param name="key">登録用のキー文字列</param>
    /// <param name="path">画像ファイルのパス</param>
    /// <param name="start">分割開始位置（左上座標、ピクセル単位）</param>
    /// <param name="num">分割する枚数（横方向・縦方向のセル数）</param>
    /// <param name="size">1セルあたりのサイズ（幅・高さ）</param>
    /// <returns>ロードして追加されたスプライトの総数</returns>
    int LoadGridCenter(const std::wstring& key, const std::wstring& path,
        DxPlus::Vec2Int start, DxPlus::Vec2Int num, DxPlus::Vec2Int size)
    {
        return LoadGrid<DxPlus::Sprite::SpriteCenter>(key, path, start, num, size);
    }
    /// <summary>
    /// 指定した画像を分割し、下端を原点とするスプライトを読み込む
    /// </summary>
    /// <param name="key">リソース登録用のキー</param>
    /// <param name="path">画像ファイルのパス</param>
    /// <param name="start">分割開始位置（ピクセル単位）</param>
    /// <param name="num">分割数（横×縦）</param>
    /// <param name="size">1枚あたりのサイズ（ピクセル単位）</param>
    /// <returns>登録されたスプライト数</returns>
    int LoadGridBottom(const std::wstring& key, const std::wstring& path,
        DxPlus::Vec2Int start, DxPlus::Vec2Int num, DxPlus::Vec2Int size)
    {
        return LoadGrid<DxPlus::Sprite::SpriteBottom>(key, path, start, num, size);
    }

    /// <summary>
    /// 指定した画像ファイルを読み込み、左上を原点とするスプライトを生成する
    /// </summary>
    /// <param name="key">リソース登録用のキー</param>
    /// <param name="path">画像ファイルのパス</param>
    /// <returns>生成されたスプライト（SpriteBaseポインタ）</returns>
    const DxPlus::Sprite::SpriteBase* LoadTextureAsSpriteLeftTop(
        const std::wstring& key, const std::wstring& path)
    {
        return LoadTextureAsSprite<DxPlus::Sprite::SpriteLeftTop>(key, path);
    }
    /// <summary>
    /// 指定した画像ファイルを読み込み、中央を原点とするスプライトを生成する
    /// </summary>
    /// <param name="key">リソース登録用のキー</param>
    /// <param name="path">画像ファイルのパス</param>
    /// <returns>生成されたスプライト（SpriteBaseポインタ）</returns>
    const DxPlus::Sprite::SpriteBase* LoadTextureAsSpriteCenter(
        const std::wstring& key, const std::wstring& path)
    {
        return LoadTextureAsSprite<DxPlus::Sprite::SpriteCenter>(key, path);
    }
    /// <summary>
    /// 指定した画像ファイルを読み込み、足元を原点とするスプライトを生成する
    /// </summary>
    /// <param name="key">リソース登録用のキー</param>
    /// <param name="path">画像ファイルのパス</param>
    /// <returns>生成されたスプライト（SpriteBaseポインタ）</returns>
    const DxPlus::Sprite::SpriteBase* LoadTextureAsSpriteBottom(
        const std::wstring& key, const std::wstring& path)
    {
        return LoadTextureAsSprite<DxPlus::Sprite::SpriteBottom>(key, path);
    }
    /// <summary>
    /// グリッド状に分割されたスプライトから指定位置のセルを取得します。
    /// </summary>
    /// <param name="key">取得対象のスプライトを識別するキー</param>
    /// <param name="x">グリッドの横方向インデックス（既定値 0）</param>
    /// <param name="y">グリッドの縦方向インデックス（既定値 0）</param>
    /// <returns>指定セルのスプライト（存在しない場合は nullptr）</returns>
    const DxPlus::Sprite::SpriteBase* GridAt(const std::wstring& key, int x = 0, int y = 0);
    void UnloadGrids();

    int GetMusic(const std::wstring& key);
    int GetSound(const std::wstring& key);

private:
    int LoadMusic(const std::wstring& key, const std::wstring& path);
    int LoadSound(const std::wstring& key, const std::wstring& path);
    void UnloadMusics();
    void UnloadSounds();

    int LoadFont(const std::wstring& fontName, const std::wstring& path);
    void UnloadFont(const std::wstring& fontName);
    void UnloadFonts();
 
    ResourceManager() = default;
    ~ResourceManager() = default;

    // コピー禁止
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    struct GridInfo
    {
        std::vector<DxPlus::Sprite::SpriteBase> frames; // by value（ムーブ前提）
        DxPlus::Vec2Int num; // {xNum, yNum}
    };

    struct FontInfo
    {
        int handle{ -1 };
        std::wstring path{};
    };

    std::unordered_map<std::wstring, GridInfo> grids;
    std::unordered_map<std::wstring, FontInfo> fonts;
    std::unordered_map<std::wstring, int> musics;
    std::unordered_map<std::wstring, int> sounds;
};
/// <summary>
/// ResourceManager のシングルトンインスタンスを取得するショートカット
/// </summary>
/// <returns>ResourceManager インスタンスの参照</returns>
inline ResourceManager& RM() { return ResourceManager::GetInstance(); } // ショートカット

/// <summary>
/// スプライトシートをグリッド状に分割してロードし、指定キーで管理します。
/// </summary>
/// <typeparam name="TSprite">格納するスプライト型（SpriteBaseを継承）</typeparam>
/// <param name="key">登録用のキー文字列</param>
/// <param name="path">画像ファイルのパス</param>
/// <param name="start">分割開始位置（左上座標、ピクセル単位）</param>
/// <param name="num">分割する枚数（横方向・縦方向のセル数）</param>
/// <param name="size">1セルあたりのサイズ（幅・高さ）</param>
/// <returns>ロードして追加されたスプライトの総数</returns>
template <typename TSprite>
inline int ResourceManager::LoadGrid(const std::wstring& key, const std::wstring& path, 
    DxPlus::Vec2Int start, DxPlus::Vec2Int num, DxPlus::Vec2Int size)
{
    const int xNum = num.x, yNum = num.y, all = xNum * yNum;
    if (all <= 0 || all > 256)
    {
        DxPlus::Utils::FatalError(L"ResourceManager::LoadGrid: invalid frame count");
        return -1;
    }

    // 上書き登録は許可（再登録時は中身入れ替え）
    auto& g = grids[key];
    g.num = num;
    g.frames.clear();
    g.frames.reserve(all);

    for (int y = 0; y < yNum; ++y)
    {
        for (int x = 0; x < xNum; ++x)
        {
            const int sx = start.x + x * size.x;
            const int sy = start.y + y * size.y;

            int gid = DxPlus::Sprite::Load(
                path,
                DxPlus::Vec2(float(sx), float(sy)),
                DxPlus::Vec2(float(size.x), float(size.y))
            );
            if (gid == -1)
            {
                DxPlus::Utils::FatalError(L"ResourceManager::LoadGrid: subimage load failed");
                return -1;
            }
            TSprite s;
            s.Init(gid);
            g.frames.push_back(std::move(s));
        }
    }

    return all;
}

/// <summary>
/// 指定した画像ファイルを読み込み、1枚のスプライトとして登録します。
/// </summary>
/// <typeparam name="TSprite">格納するスプライト型（SpriteBaseを継承）</typeparam>
/// <param name="key">登録用のキー文字列</param>
/// <param name="path">画像ファイルのパス</param>
/// <returns>登録されたスプライトへのポインタ（失敗時は nullptr）</returns>
template <typename TSprite>
inline const DxPlus::Sprite::SpriteBase* ResourceManager::LoadTextureAsSprite(
    const std::wstring& key, const std::wstring& path)
{
    const int id = DxPlus::Sprite::Load(path);
    if (id == -1)
    {
        DxPlus::Utils::FatalError((std::wstring(L"Failed to load texture: ") + path).c_str());
        return nullptr;
    }

    auto& g = grids[key];
    g.num = { 1,1 };
    g.frames.clear();
    g.frames.reserve(1);

    TSprite s;
    s.Init(id);
    g.frames.push_back(std::move(s));

    return &g.frames[0];
}
