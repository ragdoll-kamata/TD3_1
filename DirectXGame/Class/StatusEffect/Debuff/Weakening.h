#pragma once
#include "Debuff.h"
class Weakening : public Debuff {
	// Debuff を介して継承されました
	void PeculiarInitialize() override;
	void ApplyEffect() override;
};
