#include "Stage.h"

Stage& Stage::GetInstance()
{
	static Stage inst;
	return inst;
}

void Stage::Initialize()
{
	stageGrids.clear();

	//位置用のカウント
	int countY = 0;
	int countX = 0;

	//(重いので二回に一回何もなくしている関係で "/ 2")
	for (int y = 0; y < stageHeight / 2 + 1; y++)
	{
		//y軸に要素追加
		std::list<std::unique_ptr<Grid>>gridY;
		stageGrids.push_back(std::move(gridY));

		//(重いので二回に一回何もなくしている関係で "/ 2")
		for (int x = 0; x < stageWidth / 2 + 1; x++)
		{
			//イテレータ(Y軸)
			std::list<std::list< std::unique_ptr<Grid>>>::iterator itrY = stageGrids.end();
			itrY--;//end()は最後の要素の一個後ろなので

			//X軸に要素追加
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
	//まずy軸
	for (std::list<std::list< std::unique_ptr<Grid>>>::iterator itrY = stageGrids.begin(); itrY != stageGrids.end(); itrY++)
	{
		//x軸
		for (std::list< std::unique_ptr<Grid>>::iterator itrX = itrY->begin(); itrX != itrY->end(); itrX++)
		{
			itrX->get()->Draw();
		}
	}
}

void Stage::OnTheGrid(Vector2 pos, int walkNum)
{
	//y軸
	std::list<std::list< std::unique_ptr<Grid>>>::iterator itrY = stageGrids.begin();
	//ｙの分進める//(重いので二回に一回何もなくしている関係で "/ 2")
	std::advance(itrY, (int)pos.y / 2);

	//x軸
	std::list< std::unique_ptr<Grid>>::iterator itrX = itrY->begin();
	//xの分進める(重いので二回に一回何もなくしている関係で　/ 2)
	std::advance(itrX, (int)pos.x / 2);

	//すでに塗られていたら囲う
	if (itrX->get()->GetIsPainted() && itrX->get()->GetWalkNum() < walkNum)
	{
		EncloseGrid(itrX->get()->GetWalkNum(), walkNum);
	}
	else
	{
		//塗られたフラグをオン
		itrX->get()->SetIsPainted(true);
	}
	//カウントセット
	itrX->get()->SetWalkNum(walkNum);
}

void Stage::EncloseGrid(int lowNum, int highNum)
{
	//囲う用のフラグ
	bool isEnclose[2] = { false,false };

	int countX = 0;
	//範囲内に含まれているカウントの数
	int innerNumCount = 0;

	//まずy軸
	for (std::list<std::list< std::unique_ptr<Grid>>>::iterator itrY = stageGrids.begin(); itrY != stageGrids.end(); itrY++)
	{
		//x軸

		//先ずは範囲内のカウントの数を調べる
		for (std::list< std::unique_ptr<Grid>>::iterator itrX = itrY->begin(); itrX != itrY->end(); itrX++)
		{
			if (itrX->get()->GetWalkNum() < highNum && itrX->get()->GetWalkNum() >= lowNum)
			{
				innerNumCount++;
			}
		}

		//塗っていく
		for (std::list< std::unique_ptr<Grid>>::iterator itrX = itrY->begin(); itrX != itrY->end(); itrX++)
		{
			//囲い始め(歩かれたマスで、囲ったwalkNumの間のマスであれば)
			if (!isEnclose[0] && !isEnclose[1] &&
				itrX->get()->GetWalkNum() < highNum && itrX->get()->GetWalkNum() >= lowNum &&
				itrX->get()->GetIsPainted())
			{
				isEnclose[0] = true;
				isEnclose[1] = true;
			}
			//囲う途中
			else if (isEnclose[0])
			{
				//囲ったwalkNumの間のマスに到達したら、塗り終わる(範囲内のカウントが一個だけだった時も)
				if (itrX->get()->GetWalkNum() < highNum && itrX->get()->GetWalkNum() >= lowNum || innerNumCount < 2)
				{
					isEnclose[0] = false;
					break;
				}

				itrX->get()->SetIsPainted(true);
				//itrX->get()->SetWalkNum(highNum);
			}

			//カウント
			countX++;


		}
		//列終わったらリセット
		isEnclose[1] = false;
		isEnclose[0] = false;
		countX = 0;
		innerNumCount = 0;
	}
}
