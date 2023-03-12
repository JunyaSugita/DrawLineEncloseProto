#pragma once
#include "Grid.h"
#include <list>
#include <vector>
#include <memory>


class Stage final
{
public:
	//�X�e�[�W�T�C�Y
	static const int stageWidth = 600;
	static const int stageHeight = 360;
	
	static const int gridDistance = 2;

private:
	//�X�e�[�W�̃}�X�ڂ̔z��
	std::list<std::list< std::unique_ptr<Grid>>> stageGrids;


private:
	Stage() { ; }
	~Stage() { ; }

public:
	//�R�s�[�R���X�g���N�^�𖳌�
	Stage(const Stage& obj) = delete;
	//������Z�q��
	Stage& operator=(const Stage& obj) = delete;

public:
	static Stage& GetInstance();

	void Initialize();
	void Update();
	void Draw();

	//�h��
	void OnTheGrid(Vector2 pos, int walkNum = 0);
	//�͂܂ꂽ�Ƃ����h��
	void EncloseGrid(int beforeNum, int nowNum);
};

