#include "Player.h"
#include "DxLib.h"
#include "Stage.h"
#include "Util.h"

void Player::Initialize(Vector2 pos)
{
	this->pos = pos;
}

void Player::Update()
{
	pos.x += ((int)(CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) - (int)(CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))) * 2;
	pos.y += ((int)(CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S)) - (int)(CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))) * 2;

	//êßå¿
	pos.x = clamp(pos.x, 0.0f, (float)Stage::stageWidth);
	pos.y = clamp(pos.y, 0.0f, (float)Stage::stageHeight);
}

void Player::Draw()
{
	DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 55));
}
