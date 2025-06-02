#pragma once
#include "EnemyAction.h"
class DebuffShieldAction : public EnemyAction {
public:


// EnemyAction を介して継承されました
	void Execute() override;
};
