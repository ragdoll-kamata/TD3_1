#pragma once
#include "BattleManager.h"
#include <string>
#include"Status.h"
class Enemy;
class EnemyAction {
public:

	virtual ~EnemyAction() = default;

	void Initialize(Status* status, int value, int value2 = 0, Enemy* enemy = nullptr);

	virtual void Execute() = 0; // 純粋仮想関数

	void SetBattleManager(BattleManager* battleManager) { battleManager_ = battleManager; }
	
	void SetStatusEffectName(std::string statusEffectName) { statusEffectName_ = statusEffectName; }
	void SetStack(int stack) { stack_ = stack; }

protected:
	Status* status_;
	BattleManager* battleManager_ = nullptr;
	Enemy* enemy_ = nullptr;

	std::string statusEffectName_;
	int value_;
	int value2_;
	int stack_;
};
