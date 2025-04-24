#pragma once
#include "Buff.h"
class AurOfDeath : public Buff {
	void PeculiarInitialize() override;
	void ApplyEffect() override;
};
