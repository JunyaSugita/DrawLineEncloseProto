#pragma once
#include "Grid.h"
#include <list>
#include <vector>
#include <memory>


class Stage final
{
public:
	//ステージサイズ
	static const int stageWidth = 600;
	static const int stageHeight = 360;
	
	static const int gridDistance = 2;

private:
	//ステージのマス目の配列
	std::list<std::list< std::unique_ptr<Grid>>> stageGrids;


private:
	Stage() { ; }
	~Stage() { ; }

public:
	//コピーコンストラクタを無効
	Stage(const Stage& obj) = delete;
	//代入演算子も
	Stage& operator=(const Stage& obj) = delete;

public:
	static Stage& GetInstance();

	void Initialize();
	void Update();
	void Draw();

	//塗る
	void OnTheGrid(Vector2 pos, int walkNum = 0);
	//囲まれたところを塗る
	void EncloseGrid(int beforeNum, int nowNum);
};

