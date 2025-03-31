#pragma once
#include "StatusEffect.h"
class Debuff : public StatusEffect {
public:
	virtual ~Debuff() = default;

	virtual void PeculiarInitialize() override = 0;
	virtual void ApplyEffect() override = 0;
};
