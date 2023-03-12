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
	for (int y = 0; y < stageHeight / gridDistance + 1; y++)
	{
		//y���ɗv�f�ǉ�
		std::list<std::unique_ptr<Grid>>gridY;
		stageGrids.push_back(std::move(gridY));

		//(�d���̂œ��Ɉ�񉽂��Ȃ����Ă���֌W�� "/ 2")
		for (int x = 0; x < stageWidth / gridDistance + 1; x++)
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
	////���͂�9�}�X�S�Ē��ׂ�
	//bool isEnclose = false;
	//for (int i = -1; i < 2; i++)
	//{
	//	if (isEnclose) { break; }

	//	//y��
	//	std::list<std::list< std::unique_ptr<Grid>>>::iterator itrY = stageGrids.begin();
	//	//���S�𓾂�
	//	std::advance(itrY, (int)(pos.y / (float)gridDistance));
	//	//���̕��i�߂�(-1�`1)
	//	std::advance(itrY, i);

	//	for (int j = 0; j < 3; j++)
	//	{
	//		//x��
	//		std::list< std::unique_ptr<Grid>>::iterator itrX = itrY->begin();
	//		//���S�𓾂�
	//		std::advance(itrX, (int)(pos.x / (float)gridDistance));
	//		//x�̕��i�߂�(-1�`1)
	//		std::advance(itrX, j);

	//		//���łɓh���Ă�����͂�
	//		if (itrX->get()->GetIsPainted() && itrX->get()->GetWalkNum() < walkNum)
	//		{
	//			EncloseGrid(0, walkNum);
	//			isEnclose = true;
	//			break;
	//		}
	//	}
	//}


	//y��
	std::list<std::list< std::unique_ptr<Grid>>>::iterator itrY = stageGrids.begin();
	//���̕��i�߂�//(�d���̂œ��Ɉ�񉽂��Ȃ����Ă���֌W�� "/ 2")
	std::advance(itrY, (int)(pos.y / (float)gridDistance));

	//x��
	std::list< std::unique_ptr<Grid>>::iterator itrX = itrY->begin();
	//x�̕��i�߂�(�d���̂œ��Ɉ�񉽂��Ȃ����Ă���֌W�Ł@/ 2)
	std::advance(itrX, (int)(pos.x / (float)gridDistance));

	//���łɓh���Ă�����͂�
	if (itrX->get()->GetIsPainted() && itrX->get()->GetWalkNum() < walkNum)
	{
		EncloseGrid(itrX->get()->GetWalkNum(), walkNum);
	}
	//else
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
		//��I������烊�Z�b�g
		isEnclose[1] = false;
		isEnclose[0] = false;
		countX = 0;
		innerNumCount = 0;

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
				innerNumCount--;
			}
			else
			{
				//�͂���walkNum�̊Ԃ̃}�X�ɓ��B������A�h��I���(�͈͓��̃J�E���g�����������������)
				if (itrX->get()->GetWalkNum() < highNum && itrX->get()->GetWalkNum() >= lowNum)
				{
					if (innerNumCount % 2 == 0) { isEnclose[0] = true; }
					else { isEnclose[0] = false; }

					innerNumCount--;
				}
				//�͂��r��
				else if (isEnclose[0])
				{
					itrX->get()->SetIsPainted(true);
					//itrX->get()->SetWalkNum(highNum);
				}

			}
			if (innerNumCount <= 0)
			{
				break;
			}

			//�J�E���g
			countX++;


		}
	}
}
