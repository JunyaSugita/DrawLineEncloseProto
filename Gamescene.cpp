#include "Gamescene.h"

void Gamescene::Initialize()
{
	player.Initialize({ 30, 30 });
	Stage::GetInstance().Initialize();
}

void Gamescene::Update()
{
	player.Update();

	if (CheckHitKey(KEY_INPUT_R))
	{
		player.Initialize({ 30, 30 });
		Stage::GetInstance().Initialize();
	}
}

void Gamescene::Draw()
{
	player.Draw();
	Stage::GetInstance().Draw();
}
