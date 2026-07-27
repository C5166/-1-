// =============================
// Gameplay/Actors/Explosion.cpp
// =============================
#include "Explosion.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"

Explosion::Explosion(const DxPlus::Vec2& pos)
{
	position = pos;
	frameTime = 2;
	totalFrames = 10 * 3;

	DxLib::PlaySoundMem(RM().GetSound(ResourceKeys::SE_Explosion), DX_PLAYTYPE_BACK);
}

void Explosion::Update()
{
	if (++frameCount >= totalFrames * frameTime)
	{
		alive = false;
	}
}

void Explosion::Draw() const
{
	if (!alive) return;

	int frame = frameCount / frameTime;
	int x = frame % 10;
	int y = frame / 10;

	auto spr = RM().GridAt(ResourceKeys::Explosion, x, y);
	if (!spr) return;

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	spr->Draw(position, { 2,2 });
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
