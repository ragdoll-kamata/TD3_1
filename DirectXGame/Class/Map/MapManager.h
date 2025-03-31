#pragma once
#include <vector>
#include <memory>
#include <random>
#include "Node.h"

class BattleManager;
class RewardManager;

class MapManager {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(BattleManager* battleManager, RewardManager* rewardManager);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	void CollisionUpdata();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	void CreateMap();

	bool GetIsMapOpen() const { return isMapOpen; }
	void SetIsMapOpen(bool is);

	bool GetIsMove() const { return isMove; }
	void SetIsMove(bool is) { isMove = is; }

	bool IsStartDirection() const { return startblankTimer > 0; }

private:
	BattleManager* battleManager_ = nullptr;
	RewardManager* rewardManager_ = nullptr;
	Sprite back; 

	Vector2 mapBackPos;
	Sprite mapBack; 

	NodeType GetRandomNodeType(int floor);
	NodeType ReGetRandomNodeType(int floor, int x);

	bool IsRandomNodeType(int& probability, int& i, const int plus, NodeType nodeType, const int& kProbability = 0);

	// シャッフルのための乱数エンジンを用意
	std::mt19937 g; // メルセンヌ・ツイスタ（高品質な乱数生成）

	std::vector<std::vector<std::unique_ptr<Node>>> map;

	int maxfloar;
	int maxNode;
	int root = 6;
	int selectfloar = 0;
	int serectNode = -1;

	NodeType prevNodeType;
	float verticalNodeSpace = 100.0f;

	int eliteProbability = 0;
	int restProbability = 0;
	int treasureProbability = 0;
	int evectProbability = 0;
	int shopProbability = 0;

	float scroll;
	float prevWheel;

	bool isMapOpen = true;

	int startMapTimer;
	const int kStartMapTimer = 180;
	float startScroll;
	const int kStartblankTimer = 60;
	int startblankTimer;

	bool isMove = true;

	const int kDisplayMapTimer = 10;
	int displayOpenMapTimer;

	int displayCloseMapTimer;
};
