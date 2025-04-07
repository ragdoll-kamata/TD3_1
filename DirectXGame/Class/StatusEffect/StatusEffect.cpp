#include "StatusEffect.h"
using namespace KamataEngine;
using namespace MathUtility;
void StatusEffect::Initialize(int stack, Status* status) {
	stack_ = stack;
	status_ = status;
	PeculiarInitialize();
	sprite_.Initialize();
	sprite_.SetTextureRect({0.0f, 0.0f}, {120.0f, 120.0f});
	sprite_.SetSize({30.0f, 30.0f});
	numberSprite_ = std::make_unique<NumberSprite>();
	numberSprite_->Initialize({}, 0.2f, {1.0f, 1.0f});
	numberSprite_->SetNumber(stack_);
	
}

void StatusEffect::Draw() {
	sprite_.Draw();
	numberSprite_->Draw();
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
	numberSprite_->SetNumber(stack_);
}

void StatusEffect::AddStack(int stack) { 
	stack_ += stack;
	numberSprite_->SetNumber(stack_);
}

void StatusEffect::SetSpritePos(Vector2 pos) {
	sprite_.SetPosition(pos);
	numberSprite_->SetPosition(pos + Vector2{30.0f, 30.0f});
}
