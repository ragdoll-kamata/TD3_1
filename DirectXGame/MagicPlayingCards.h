#pragma once
#include "Relic.h"
class MagicPlayingCards : public Relic {
public:
	void PeculiarInitialize() override;
	void ApplyEffect() override;
};
