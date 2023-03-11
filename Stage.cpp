#include "Stage.h"

Stage& Stage::GetInstance()
{
	static Stage inst;
	return inst;
}

void Stage::Initialize()
{
	stageGrids.clear();

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

	//���łɓh���Ă�����͂�
	if (itrX->get()->GetIsPainted() && itrX->get()->GetWalkNum() < walkNum)
	{
		EncloseGrid(itrX->get()->GetWalkNum(), walkNum);
	}
	else
	{
		//�h��ꂽ�t���O���I��
		itrX->get()->SetIsPainted(true);
	}
	//�J�E���g�Z�b�g
	itrX->get()->SetWalkNum(walkNum);
}

void Stage::EncloseGrid(int lowNum, int highNum)
{
	//�͂��p�̃t���O
	bool isEnclose[2] = { false,false };

	int countX = 0;
	//�͈͓��Ɋ܂܂�Ă���J�E���g�̐�
	int innerNumCount = 0;

	//�܂�y��
	for (std::list<std::list< std::unique_ptr<Grid>>>::iterator itrY = stageGrids.begin(); itrY != stageGrids.end(); itrY++)
	{
		//x��

		//�悸�͔͈͓��̃J�E���g�̐��𒲂ׂ�
		for (std::list< std::unique_ptr<Grid>>::iterator itrX = itrY->begin(); itrX != itrY->end(); itrX++)
		{
			if (itrX->get()->GetWalkNum() < highNum && itrX->get()->GetWalkNum() >= lowNum)
			{
				innerNumCount++;
			}
		}

		//�h���Ă���
		for (std::list< std::unique_ptr<Grid>>::iterator itrX = itrY->begin(); itrX != itrY->end(); itrX++)
		{
			//�͂��n��(�����ꂽ�}�X�ŁA�͂���walkNum�̊Ԃ̃}�X�ł����)
			if (!isEnclose[0] && !isEnclose[1] &&
				itrX->get()->GetWalkNum() < highNum && itrX->get()->GetWalkNum() >= lowNum &&
				itrX->get()->GetIsPainted())
			{
				isEnclose[0] = true;
				isEnclose[1] = true;
			}
			//�͂��r��
			else if (isEnclose[0])
			{
				//�͂���walkNum�̊Ԃ̃}�X�ɓ��B������A�h��I���(�͈͓��̃J�E���g�����������������)
				if (itrX->get()->GetWalkNum() < highNum && itrX->get()->GetWalkNum() >= lowNum || innerNumCount < 2)
				{
					isEnclose[0] = false;
					break;
				}

				itrX->get()->SetIsPainted(true);
				//itrX->get()->SetWalkNum(highNum);
			}

			//�J�E���g
			countX++;


		}
		//��I������烊�Z�b�g
		isEnclose[1] = false;
		isEnclose[0] = false;
		countX = 0;
		innerNumCount = 0;
	}
}
