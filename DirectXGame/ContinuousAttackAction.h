#pragma once
#include "EnemyAction.h"
class ContinuousAttackAction : public EnemyAction {
public:
	void Execute() override;
};
