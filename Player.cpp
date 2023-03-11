#include "Player.h"
#include "DxLib.h"
#include "Stage.h"
#include "Util.h"
#include<string>

void Player::Initialize(Vector2 pos)
{
	this->pos = pos;
	walkCount = 0;
}

void Player::Update()
{
	//1フレーム前の座標
	oldPos = pos;

	//移動
	pos.x += ((int)(CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) - (int)(CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))) * 2.0f;
	pos.y += ((int)(CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S)) - (int)(CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))) * 2.0f;

	//制限
	pos.x = clamp(pos.x, 0.0f, (float)Stage::stageWidth);
	pos.y = clamp(pos.y, 0.0f, (float)Stage::stageHeight);

	//前フレームから動いていたら
	if (oldPos.x != pos.x || oldPos.y != pos.y)
	{
		walkCount++;

		//塗る
		Stage::GetInstance().OnTheGrid(pos, walkCount);
	}
}

void Player::Draw()
{
	DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 55));

	char walkNumC[11] = { 0 };
	//intを文字列に変換
	_itoa_s(walkCount, walkNumC, _countof(walkNumC) - 1);
	DrawFormatString(0, 0, GetColor(255, 255, 255), walkNumC);
}
