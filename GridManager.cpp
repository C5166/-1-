#include "GridManager.h"
#include "DxLib.h"

GridManager::GridManager() {
    std::random_device rd;
    m_rng = std::mt19937(rd());
}

GridManager::~GridManager() {
}

void GridManager::Initialize(int width, int height, float tileSize, const DxPlus::Vec2& offset) {
    m_width = width;
    m_height = height;
    m_tileSize = tileSize;
    m_offset = offset;

    m_gridData.assign(m_width * m_height, TileType::None);

    // 1. 最下層（地面: インデックス Y = m_height - 1）を作成
    int bottomY = m_height - 1;
    for (int x = 0; x < m_width; ++x) {
        SetTile(x, bottomY, TileType::HeavyBlock);
    }

    // 地面の1つ上の行から順に生成を開始する
    m_generatedRow = bottomY - 1;

    // 2. 最初に画面内（15行分）を確実に生成する
    int initialRows = 15;
    for (int i = 0; i < initialRows; ++i) {
        if (m_generatedRow >= 0) {
            GenerateRow(m_generatedRow);
            m_generatedRow--;
        }
    }
}

void GridManager::GenerateRow(int targetY) {
    if (targetY < 0 || targetY >= m_height) return;

    // 頂上（Y = 0）ならゴールを配置
    if (targetY == 0) {
        SetTile(m_width / 2, 0, TileType::Goal);
        return;
    }

    // ブロックの生成
    int wallCount = 0;
    for (int x = 0; x < m_width; ++x) {
        int randVal = m_rng() % 100;

        // 壁（固定ブロック）
        if (randVal < 15 && wallCount < m_width - 2) {
            SetTile(x, targetY, TileType::HeavyBlock);
            wallCount++;
        }
        // 通常ブロック（動かせる青ブロック）
        else if (randVal < 40) {
            SetTile(x, targetY, TileType::NormalBlock);
        }
    }
}

void GridManager::Update(float deltaTime, float cameraY) {
    int currentTopRow = static_cast<int>((cameraY - m_offset.y) / m_tileSize);

    // 画面上端からさらに 10行先まで先行して生成しておく
    int targetRow = currentTopRow - 10;
    if (targetRow < 0) targetRow = 0;

    // まだ生成していない上部の行があれば、そこまで動的追加
    while (m_generatedRow >= targetRow && m_generatedRow >= 0) {
        GenerateRow(m_generatedRow);
        m_generatedRow--;
    }


	//デバッグ用十字キーでキーが押されたときX軸やY軸方向に画面をスクロールさせる
#ifdef _DEBUG

    using namespace DxPlus::Input;

	int button = GetButton(PLAYER1);

    if (button & BUTTON_UP) {
        m_offset.y -= 5.0f;
	}

    if (button & BUTTON_DOWN) {
        m_offset.y += 5.0f;
	}

#endif 

}

void GridManager::Draw(float cameraY, float screenHeight) const {
    // 描画範囲の計算（画面内 ＋ 上下2マス）
    int startY = static_cast<int>((cameraY - m_offset.y) / m_tileSize) - 2;
    int endY = startY + static_cast<int>(screenHeight / m_tileSize) + 4;

    if (startY < 0) startY = 0;
    if (endY >= m_height) endY = m_height - 1;

    for (int y = startY; y <= endY; ++y) {
        for (int x = 0; x < m_width; ++x) {
            TileType type = GetTile(x, y);
            if (type == TileType::None) continue;

            DxPlus::Vec2 worldPos = GridToWorld(x, y);

            int x1 = static_cast<int>(worldPos.x);
            int y1 = static_cast<int>(worldPos.y - cameraY);
            int x2 = static_cast<int>(x1 + m_tileSize - 1);
            int y2 = static_cast<int>(y1 + m_tileSize - 1);

            if (type == TileType::NormalBlock) {
                // 青色
                DrawBox(x1, y1, x2, y2, GetColor(65, 115, 205), TRUE);
                DrawBox(x1, y1, x2, y2, GetColor(30, 60, 120), FALSE);
            }
            else if (type == TileType::HeavyBlock) {
                // グレー
                DrawBox(x1, y1, x2, y2, GetColor(160, 160, 160), TRUE);
                DrawBox(x1, y1, x2, y2, GetColor(60, 60, 60), FALSE);
            }
            else if (type == TileType::Goal) {
                // 黄色
                DrawBox(x1, y1, x2, y2, GetColor(255, 195, 0), TRUE);
                DrawBox(x1, y1, x2, y2, GetColor(180, 130, 0), FALSE);
            }
        }
    }
}

// ==================================================
// 座標変換ユーティリティ (ここが抜けていたためエラーでした)
// ==================================================

DxPlus::Vec2 GridManager::GridToWorld(int gridX, int gridY) const {
    return DxPlus::Vec2(
        m_offset.x + gridX * m_tileSize,
        m_offset.y + gridY * m_tileSize
    );
}

bool GridManager::WorldToGrid(const DxPlus::Vec2& worldPos, int& outGridX, int& outGridY) const {
    int gx = static_cast<int>((worldPos.x - m_offset.x) / m_tileSize);
    int gy = static_cast<int>((worldPos.y - m_offset.y) / m_tileSize);

    if (IsValidGrid(gx, gy)) {
        outGridX = gx;
        outGridY = gy;
        return true;
    }
    return false;
}

// ==================================================
// 盤面データへのアクセス & 操作
// ==================================================

TileType GridManager::GetTile(int gridX, int gridY) const {
    if (!IsValidGrid(gridX, gridY)) return TileType::None;
    return m_gridData[gridY * m_width + gridX];
}

void GridManager::SetTile(int gridX, int gridY, TileType type) {
    if (IsValidGrid(gridX, gridY)) {
        m_gridData[gridY * m_width + gridX] = type;
    }
}

bool GridManager::IsValidGrid(int gridX, int gridY) const {
    return (gridX >= 0 && gridX < m_width && gridY >= 0 && gridY < m_height);
}

bool GridManager::MoveBlock(int fromX, int fromY, int toX, int toY) {
    if (!IsValidGrid(fromX, fromY) || !IsValidGrid(toX, toY)) return false;

    if (GetTile(fromX, fromY) == TileType::NormalBlock && GetTile(toX, toY) == TileType::None) {
        SetTile(toX, toY, TileType::NormalBlock);
        SetTile(fromX, fromY, TileType::None);
        return true;
    }
    return false;
}