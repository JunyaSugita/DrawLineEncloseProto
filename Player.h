#pragma once
#include"Vector2.h"

class Player
{
private:
	//À•W
	Vector2 pos;
	//
	float radius = 3;
public:
	void Initialize(Vector2 pos);

	void SetPos(Vector2 pos) { this->pos = pos; }
	Vector2 GetPos() { return pos; }

	void Update();
	void Draw();
};

