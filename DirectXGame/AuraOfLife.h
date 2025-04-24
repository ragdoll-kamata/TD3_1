#pragma once
#include "StatusEffect.h"
class AuraOfLife : public StatusEffect {
public:
	void PeculiarInitialize() override;
	void ApplyEffect() override;
};
