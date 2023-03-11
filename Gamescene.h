#pragma once
#include"Stage.h"
#include"Player.h"


class Gamescene
{
private:
	Player player;

public:

	void Initialize();
	void Update();
	void Draw();
};

