#pragma once
#include "Buff.h"
class Regeneration : public Buff {
	// Buff を介して継承されました
	void PeculiarInitialize() override;
	void ApplyEffect() override;
};
