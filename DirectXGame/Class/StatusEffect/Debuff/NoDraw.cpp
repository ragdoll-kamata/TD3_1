#include "NoDraw.h"
#include "CardManager.h"

void NoDraw::PeculiarInitialize() {
	effectTiming_ = EffectTiming::OnDraw;
	stackDecreaseTiming_ = StackDecreaseTiming::StartOfTurn;
}

void NoDraw::ApplyEffect() {
	cardManager_->SetCardDrawNum(0);
}