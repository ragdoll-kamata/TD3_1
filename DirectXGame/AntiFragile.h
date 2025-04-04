#pragma once
#include "Buff.h"
class AntiFragile : public Buff {
	void PeculiarInitialize() override;
	void ApplyEffect() override;
};
