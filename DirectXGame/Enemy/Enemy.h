#pragma once
#include <vector>
#include <memory>
#include <KamataEngine.h>
#include "NumberSprite.h"

#include "EnemyAction.h"

using namespace KamataEngine;

class BattleManager;

class Enemy {
public:
	virtual ~Enemy() = default;
	enum class EnemyTurn {
		Standby,
		Start,
		Main,
		End,
	};

	virtual void Initialize() = 0;

	void Update();


	void StartEnemyTurn();

	virtual void PredictNextAction() = 0;
	void Draw();

	bool StartMainTurn();

	bool MainTurn();

	bool EndMainTurn();

	void StartBattle();

	virtual void StartBattlePeculiar() = 0;

	bool IsOnCollision(Vector2 pos);

	int GetHP() const { return HP; }
	void DamageHP(int hp) { HP -= hp; }


	void SetBattleManager(BattleManager* battleManager) { battleManager_ = battleManager; }

	EnemyTurn GetEnemyTurn() const { return enemyTurn; }

protected:
	BattleManager* battleManager_ = nullptr;

	Sprite sprite;
	uint32_t TH;
	NumberSprite numberSprite;

	Vector2 pos_;
	Vector2 halfSize;

	std::unique_ptr<EnemyAction> enemyAction;
	std::unique_ptr<EnemyAction> reverseEnemyAction;
	int index = 0;
	int value;
	int HP;
	int maxHP;
	bool isReverse = false;
	EnemyTurn enemyTurn = EnemyTurn::End;
};
