#pragma once
#include "Relic.h"
class BlankRelic : public Relic {
public:
	void PeculiarInitialize() override {
		effectTiming_ = RelicEffectTiming::None;
	}
	void ApplyEffect() override {}


};
