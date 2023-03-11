#include "Stage.h"

Stage& Stage::GetInstance()
{
	static Stage inst;
	return inst;
}

void Stage::Initialize()
{
	//�ʒu�p�̃J�E���g
	int countY = 0;
	int countX = 0;

	//(�d���̂œ��Ɉ�񉽂��Ȃ����Ă���֌W�� "/ 2")
	for (int y = 0; y < stageHeight / 2 + 1; y++)
	{
		//y���ɗv�f�ǉ�
		std::list<std::unique_ptr<Grid>>gridY;
		stageGrids.push_back(std::move(gridY));

		//(�d���̂œ��Ɉ�񉽂��Ȃ����Ă���֌W�� "/ 2")
		for (int x = 0; x < stageWidth / 2 + 1; x++)
		{
			//�C�e���[�^(Y��)
			std::list<std::list< std::unique_ptr<Grid>>>::iterator itrY = stageGrids.end();
			itrY--;//end()�͍Ō�̗v�f�̈���Ȃ̂�

			//X���ɗv�f�ǉ�
			std::unique_ptr<Grid>gridX = std::make_unique<Grid>();
			gridX->Initialize({ (float)countX * 2,(float)countY * 2 });
			itrY->push_back(std::move(gridX));

			countX++;
		}
		countY++;
		countX = 0;
	}
}

void Stage::Update()
{
}

void Stage::Draw()
{
	//�܂�y��
	for (std::list<std::list< std::unique_ptr<Grid>>>::iterator itrY = stageGrids.begin(); itrY != stageGrids.end(); itrY++)
	{
		//x��
		for (std::list< std::unique_ptr<Grid>>::iterator itrX = itrY->begin(); itrX != itrY->end(); itrX++)
		{
			itrX->get()->Draw();
		}
	}
}

void Stage::OnTheGrid(Vector2 pos, int walkNum)
{
	//y��
	std::list<std::list< std::unique_ptr<Grid>>>::iterator itrY = stageGrids.begin();
	//���̕��i�߂�//(�d���̂œ��Ɉ�񉽂��Ȃ����Ă���֌W�� "/ 2")
	std::advance(itrY, (int)pos.y / 2);

	//x��
	std::list< std::unique_ptr<Grid>>::iterator itrX = itrY->begin();
	//x�̕��i�߂�(�d���̂œ��Ɉ�񉽂��Ȃ����Ă���֌W�Ł@/ 2)
	std::advance(itrX, (int)pos.x / 2);

	//�h��ꂽ�t���O���I��
	itrX->get()->SetIsPainted(true);
}
