#pragma once
#include"Vector2.h"

class Player
{
private:
	//座標
	Vector2 pos;
	Vector2 oldPos;
	//
	float radius = 3;

	//囲う用の歩いたカウント
	int walkCount = 0;

public:
	void Initialize(Vector2 pos);

	void SetPos(Vector2 pos) { this->pos = pos; }
	Vector2 GetPos() { return pos; }

	void Update();
	void Draw();
};

