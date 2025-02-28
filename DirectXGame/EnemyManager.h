#pragma once
#include <memory>
#include <vector>
#include "Enemy.h"
#include <math/Vector2.h>
using namespace KamataEngine;
class EnemyManager {
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


	uint32_t IsOnCollision(Vector2 pos);

	Enemy* GetEnemy(const uint32_t& EH);

private:
	std::vector<std::unique_ptr<Enemy>> enemy;

};
