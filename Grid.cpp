#include "Grid.h"

void Grid::Initialize(Vector2 pos, bool isPainted, int walkNum)
{
	this->pos = pos;
	this->isPainted = isPainted;
	this->walkNum = walkNum;
}

void Grid::Draw()
{
	//“h‚ç‚ê‚½‚ç•`‰æ
	if (isPainted) 
	{
		DrawBox(pos.x, pos.y, pos.x, pos.y, GetColor(255, 255, 255), false);
	}
}
