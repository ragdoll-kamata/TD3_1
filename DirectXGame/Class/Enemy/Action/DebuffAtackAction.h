#pragma once
#include "EnemyAction.h"
class DebuffAtackAction : public EnemyAction {
public:
	void Execute() override;
};
