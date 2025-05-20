#pragma once
#include "Debuff.h"
class NoDraw : public Debuff {
public:
	// Debuff を介して継承されました
	void PeculiarInitialize() override;
	void ApplyEffect() override;
};
