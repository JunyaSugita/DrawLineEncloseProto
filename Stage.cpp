#include "Stage.h"

Stage& Stage::GetInstance()
{
	static Stage inst;
	return inst;
}

void Stage::Initialize()
{
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

	//塗られたフラグをオン
	itrX->get()->SetIsPainted(true);
}
