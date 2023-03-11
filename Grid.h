#pragma once
#include"DxLib.h"
#include"Vector2.h"


class Grid
{
public:
	//歩かれてないマスの識別用数字
	static const int notWalkedNum = -1;
private:
	//囲われて塗られているかどうか
	bool isPainted = false;
	//歩かれたときに、入れるカウント（囲むときに使う）
	int walkNum = notWalkedNum;
	//座標
	Vector2 pos = {};

public:

	void Initialize(Vector2 pos, bool isPainted = false, int walkNum = notWalkedNum);

	//塗られているかを返す
	bool GetIsPainted() { return isPainted; }
	//歩かれたときのカウントを返す
	int GetWalkNum() { return walkNum; }
	//
	Vector2 GetPos() { return pos; }

	//塗られているかをセット
	void SetIsPainted(bool is) { isPainted = is; }
	//歩かれたときのカウントをセット
	void SetWalkNum(int num) { walkNum = num; }
	//
	void SetPos(Vector2 pos) { this->pos = pos; }

	void Draw();

};

