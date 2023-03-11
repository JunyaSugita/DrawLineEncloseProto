#include "Gamescene.h"

void Gamescene::Initialize()
{
	player.Initialize({ 0, 0 });
	Stage::GetInstance().Initialize();
}

void Gamescene::Update()
{
	player.Update();

	//“h‚é
	Stage::GetInstance().OnTheGrid(player.GetPos());
}

void Gamescene::Draw()
{
	player.Draw();
	Stage::GetInstance().Draw();
}
