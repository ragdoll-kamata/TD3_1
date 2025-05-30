#include "NoDraw.h"
#include "CardManager.h"

void NoDraw::PeculiarInitialize() {
	effectTiming_ = EffectTiming::OnDraw;
	stackDecreaseTiming_ = StackDecreaseTiming::EndOfTurn;
}

void NoDraw::ApplyEffect() {
	cardManager_->SetCardDrawNum(0);
}