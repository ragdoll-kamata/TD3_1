#pragma once
#include "Enemy.h"
class Boss : public Enemy {
public:
	void Initialize() override;

// Enemy を介して継承されました
	void PredictNextAction() override;
	void StartBattlePeculiar() override;

private:
	int stack = 0;
};
