#pragma once
#include "Debuff.h"
class Poison : public Debuff {
public:
	~Poison();
	void PeculiarInitialize() override;

	void ApplyEffect() override;

};
