#pragma once
#include <vector>
#include <memory>
#include <random>
#include <KamataEngine.h>

#include "EnemyAction.h"

#include "Status.h"
#include "StatusEffect.h"

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

	virtual void Initialize();

	void Update();

	virtual void PredictNextAction() = 0;
	void Draw();

	bool StartMainTurn();

	bool MainTurn();

	bool EndMainTurn();

	void StartBattle();

	virtual void StartBattlePeculiar() = 0;

	bool IsOnCollision(Vector2 pos);

	void SetBattleManager(BattleManager* battleManager) { battleManager_ = battleManager; }

	EnemyTurn GetEnemyTurn() const { return enemyTurn; }

    void AddStatusEffect(std::unique_ptr<StatusEffect> statusEffect, int stack);

	void Effect(EffectTiming effectTiming, StackDecreaseTiming stackDecreaseTiming);


	Status* GetStatus() { return status_.get(); }

	bool IsDeath() const { return isDeath; }

protected:
	BattleManager* battleManager_ = nullptr;

	Sprite sprite;
	uint32_t TH;

	Vector2 pos_;
	Vector2 halfSize;

	std::unique_ptr<EnemyAction> enemyAction;
	std::unique_ptr<EnemyAction> reverseEnemyAction;
	int index = 0;
	int value;
	bool isReverse = false;
	bool isDeath = false;
	EnemyTurn enemyTurn = EnemyTurn::End;

	std::unique_ptr<Status> status_;
	std::uniform_int_distribution<int> dist;
	std::mt19937 g; 
};
