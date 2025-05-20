#pragma once
#include "Relic.h"
class SakeCup : public Relic {
public:
	// Relic を介して継承されました
	void PeculiarInitialize() override;
	void ApplyEffect() override;

private:

};
