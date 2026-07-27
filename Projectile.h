// =============================
// Gameplay/Actors/Projectile.h
// =============================
#pragma once
#include "Entity2D.h"

class Projectile : public Entity2D
{
public:
	Projectile();
	void Init() override;
	void Reset(const DxPlus::Vec2& pos, const DxPlus::Vec2& vel) noexcept;
	void Update() override {};
	void Step() override;
};