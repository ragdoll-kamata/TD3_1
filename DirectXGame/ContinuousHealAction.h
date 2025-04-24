#pragma once
#include "EnemyAction.h"
class ContinuousHealAction : public EnemyAction {
public:
	void Execute() override;
};
