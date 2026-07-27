#pragma once

#include <vector>
#include <random>
#include "DxPlus/DxPlus.h"

enum class TileType {
    None = 0,    // 空白
    NormalBlock, // 動かせるブロック
    HeavyBlock,  // 動かせないブロック（壁）
    Goal         // ゴール
};

class GridManager {
public:
    GridManager();
    ~GridManager();

    void Initialize(int width = 10, int height = 120, float tileSize = 192.0f, const DxPlus::Vec2& offset = DxPlus::Vec2(0.0f, 0.0f));

    /// <summary>
    /// カメラの位置に応じて新しい行を動的に生成・描画更新
    /// </summary>
    void Update(float deltaTime, float cameraY);

    /// <summary>
    /// 画面内のみ描画（カリング）
    /// </summary>
    void Draw(float cameraY, float screenHeight = 1080.0f) const;

    // --- 座標変換 & 盤面操作 ---
    DxPlus::Vec2 GridToWorld(int gridX, int gridY) const;
    bool WorldToGrid(const DxPlus::Vec2& worldPos, int& outGridX, int& outGridY) const;
    TileType GetTile(int gridX, int gridY) const;
    void SetTile(int gridX, int gridY, TileType type);
    bool IsValidGrid(int gridX, int gridY) const;
    bool MoveBlock(int fromX, int fromY, int toX, int toY);

    // ゲッター
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    float GetTileSize() const { return m_tileSize; }
    DxPlus::Vec2 GetOffset() const { return m_offset; }

private:
    // 1行分だけ自動生成する処理
    void GenerateRow(int targetY);

private:
    int m_width = 10;
    int m_height = 120;
    float m_tileSize = 192.0f;
    DxPlus::Vec2 m_offset = { 0.0f, 0.0f };

    std::vector<TileType> m_gridData;
    int m_generatedRow = 0; // どこまで生成が完了したか（120からカウントダウン）
    mutable std::mt19937 m_rng;
};