#pragma once
#include "Relic.h"
class DisposableShield : public Relic {
public:

	void PeculiarInitialize() override;
	void ApplyEffect() override;

private:
	int i = 0;
};
