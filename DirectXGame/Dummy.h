#pragma once
#include "Enemy.h"
class Dummy : public Enemy {
public:
	void Initialize(Player* player) override;
};
