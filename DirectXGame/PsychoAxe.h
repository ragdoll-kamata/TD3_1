#pragma once
#include "Enemy.h"
class PsychoAxe : public Enemy {
public:
	void Initialize() override;
	void StartBattlePeculiar() override;
	void PredictNextAction() override;

};
