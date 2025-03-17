#include "StatusEffect.h"

void StatusEffect::Initialize(int stack, Status* status) {
	stack_ = stack;
	status_ = status;
	PeculiarInitialize();
}

void StatusEffect::Effect(EffectTiming effectTiming) {
	if (effectTiming == effectTiming_) {
		ApplyEffect();
		if (stackDecreaseTiming_ == StackDecreaseTiming::OnEffect) {
			DecreaseStack(StackDecreaseTiming::OnEffect);
		}
	}
}

void StatusEffect::DecreaseStack(StackDecreaseTiming timing) {
	if (timing == stackDecreaseTiming_) {
		stack_--;
	}
}
