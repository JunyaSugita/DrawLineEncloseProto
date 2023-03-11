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
	//1�t���[���O�̍��W
	oldPos = pos;

	//�ړ�
	pos.x += ((int)(CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D)) - (int)(CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))) * 2.0f;
	pos.y += ((int)(CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S)) - (int)(CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))) * 2.0f;

	//����
	pos.x = clamp(pos.x, 0.0f, (float)Stage::stageWidth);
	pos.y = clamp(pos.y, 0.0f, (float)Stage::stageHeight);

	//�O�t���[�����瓮���Ă�����
	if (oldPos.x != pos.x || oldPos.y != pos.y)
	{
		walkCount++;

		//�h��
		Stage::GetInstance().OnTheGrid(pos, walkCount);
	}
}

void Player::Draw()
{
	DrawCircle(pos.x, pos.y, radius, GetColor(255, 255, 55));

	char walkNumC[11] = { 0 };
	//int�𕶎���ɕϊ�
	_itoa_s(walkCount, walkNumC, _countof(walkNumC) - 1);
	DrawFormatString(0, 0, GetColor(255, 255, 255), walkNumC);
}
