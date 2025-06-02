#pragma once
#include "EnemyAction.h"
class DebuffAction : public EnemyAction {
public:



// EnemyAction を介して継承されました
	void Execute() override;
};
