#pragma once
#include <vector>
#include <memory>
#include <KamataEngine.h>
#include "NumberSprite.h"

#include "EnemyAction.h"

using namespace KamataEngine;

class Player;

class Enemy {
public:
	virtual ~Enemy() = default;
	enum class EnemyTurn {
		Standby,
		Start,
		Main,
		End,
	};

	virtual void Initialize(Player* player) = 0;

	void Update();


	void StartEnemyTurn();
	void Draw();

	bool IsOnCollision(Vector2 pos);

	int GetHP() const { return HP; }
	void DamageHP(int hp) { HP -= hp; }


	void SetPlayer(Player* player) { player_ = player; }

	EnemyTurn GetEnemyTurn() const { return enemyTurn; }

protected:
	Player* player_ = nullptr;

	Sprite sprite;
	uint32_t TH;
	NumberSprite numberSprite;

	Vector2 pos_;
	Vector2 halfSize;

	std::vector<std::unique_ptr<EnemyAction>> enemyAction;
	std::vector<std::unique_ptr<EnemyAction>> reverseEnemyAction;
	int index = 0;
	int value;
	int HP;
	int maxHP;
	bool isReverse = false;
	EnemyTurn enemyTurn = EnemyTurn::Standby;
};
