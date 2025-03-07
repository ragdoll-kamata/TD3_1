#pragma once
#include "BattleManager.h"
enum class Debuff {
	Poison,

};


class EnemyAction {
public:

	virtual ~EnemyAction() = default;

	void Initialize(int value, int value2 = 0);

	virtual void Execute() = 0; // 純粋仮想関数

	void SetBattleManager(BattleManager* battleManager) { battleManager_ = battleManager; }
	
protected:
	BattleManager* battleManager_ = nullptr;

	int value_;
	int value2_;
};
