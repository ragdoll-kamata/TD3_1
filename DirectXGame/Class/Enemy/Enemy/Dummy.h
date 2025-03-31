#pragma once
#include "Enemy.h"
class Dummy : public Enemy {
public:
	void Initialize() override;

	void PredictNextAction() override;

	void StartBattlePeculiar() override;
};
