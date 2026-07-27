// =============================
// Gameplay/Actors/Explosion.h
// =============================
#pragma once
#include "Entity2D.h"

class Explosion : public Entity2D
{
public:
	explicit Explosion(const DxPlus::Vec2& pos);
	void Update() override;
	void Draw() const override;

private:
	int frameCount{ 0 };	// 経過フレーム
	int frameTime{ 0 };		// 1コマあたりの表示フレーム数
	int totalFrames{ 0 };	// 総コマ数
};
