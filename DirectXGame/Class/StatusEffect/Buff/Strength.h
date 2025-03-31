#pragma once
#include "Buff.h"
class Strength : public Buff {
	void PeculiarInitialize() override;
	void ApplyEffect() override;
};
