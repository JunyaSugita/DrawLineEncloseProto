#pragma once
#include"DxLib.h"
#include"Vector2.h"


class Grid
{
public:
	//������ĂȂ��}�X�̎��ʗp����
	static const int notWalkedNum = -1;
private:
	//�͂��ēh���Ă��邩�ǂ���
	bool isPainted = false;
	//�����ꂽ�Ƃ��ɁA�����J�E���g�i�͂ނƂ��Ɏg���j
	int walkNum = notWalkedNum;
	//���W
	Vector2 pos = {};

public:

	void Initialize(Vector2 pos, bool isPainted = false, int walkNum = notWalkedNum);

	//�h���Ă��邩��Ԃ�
	bool GetIsPainted() { return isPainted; }
	//�����ꂽ�Ƃ��̃J�E���g��Ԃ�
	int GetWalkNum() { return walkNum; }
	//
	Vector2 GetPos() { return pos; }

	//�h���Ă��邩���Z�b�g
	void SetIsPainted(bool is) { isPainted = is; }
	//�����ꂽ�Ƃ��̃J�E���g���Z�b�g
	void SetWalkNum(int num) { walkNum = num; }
	//
	void SetPos(Vector2 pos) { this->pos = pos; }

	void Draw();

};

