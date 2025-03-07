#pragma once
#include "Debuff.h"
class Poison : public Debuff {
public:

	void PeculiarInitialize() override;

	void ApplyEffect() override;

};
