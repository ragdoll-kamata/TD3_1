#pragma once
#include <vector>
#include <memory>
#include <random>
#include "Node.h"

class MapManager {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	void CreateMap();

private:



	NodeType GetRandomNodeType(int floor);

	// シャッフルのための乱数エンジンを用意
	std::mt19937 g; // メルセンヌ・ツイスタ（高品質な乱数生成）

	std::vector<std::vector<std::unique_ptr<Node>>> map;

	int maxfloar;
	int maxNode;
	int root = 5;
	int branchChance;
	NodeType prevNodeType;
};
