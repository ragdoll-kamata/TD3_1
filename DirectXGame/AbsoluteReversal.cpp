#include "AbsoluteReversal.h"
#include "CardManager.h"
void AbsoluteReversal::PeculiarInitialize() {
	effectTiming_ = EffectTiming::OnExecution;
	stackDecreaseTiming_ = StackDecreaseTiming::OnEffect;
}

void AbsoluteReversal::ApplyEffect() { cardManager_->GetExecutionCard()->SetIsReverse(true); }