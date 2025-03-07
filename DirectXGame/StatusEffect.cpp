#include "StatusEffect.h"

inline void StatusEffect::Effect(EffectTiming effectTiming) {
	if (effectTiming == effectTiming_) {
		ApplyEffect();
		if (stackDecreaseTiming_ == StackDecreaseTiming::OnEffect) {
			DecreaseStack(StackDecreaseTiming::OnEffect);
		}
	}
}

inline void StatusEffect::DecreaseStack(StackDecreaseTiming timing) {
	if (timing == stackDecreaseTiming_) {
		stack_--;
	}
}
