// =============================
// Gameplay/Actors/Projectile.cpp
// =============================
#include "Projectile.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"

Projectile::Projectile()
{
	DxLib::PlaySoundMem(RM().GetSound(ResourceKeys::SE_PlayerShot), DX_PLAYTYPE_BACK);
}

void Projectile::Init()
{
	sprite = RM().GridAt(ResourceKeys::Player_Shot);
}

void Projectile::Reset(const DxPlus::Vec2& pos, const DxPlus::Vec2& vel) noexcept
{
	position = pos;
	velocity = vel;
}

void Projectile::Step()
{
	Entity2D::Step();

	if (position.x < 0 || position.x > DxPlus::CLIENT_WIDTH
		|| position.y < 0 || position.y > DxPlus::CLIENT_HEIGHT)
	{
		Kill();
	}
}
