#pragma once
#include "Enemy.h"
class Caterpillar : public Enemy {
public:
	void Initialize() override;

	void PredictNextAction() override;

	void StartBattlePeculiar() override;
};
