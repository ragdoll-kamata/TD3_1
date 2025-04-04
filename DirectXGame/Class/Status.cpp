#include "Status.h"
#include "StatusEffect.h"
#include "math/MathUtility.h"
#include "StatusEffectPair.h"
using namespace KamataEngine;
using namespace MathUtility;
void Status::Initialize(Vector2 pos, Vector2 size, int maxHP) {
	HP_ = maxHP;
	maxHP_ = maxHP;
	shield_ = 0;
	damageRate_ = 1.0f;
	hpS.Initialize(pos + Vector2{0.0f, size.y / 2.0f}, 0.5f, Center::Central);
	shieldS.Initialize(pos + Vector2{0.0f, size.y / 2.0f + 40.0f}, 0.5f, Center::Central);
}

void Status::Update() {
	hpS.SetNumber(HP_);
	shieldS.SetNumber(shield_);
}

void Status::Draw() {
	hpS.Draw();
	if (shield_ != 0) {
		shieldS.Draw();
	}
}

void Status::ApplyDirectDamage(int damage) {
	Effect(EffectTiming::OnDamage, StackDecreaseTiming::OnDamage);
	HP_ -= damage;
}

void Status::Damage(int damage, Status* status) {
	if (status) {
		status->SetBonusDamage(0);
		status->Effect(EffectTiming::BonusDamage, StackDecreaseTiming::None);
		if (status->GetBonusDamage() != 0) {
			damage += status->GetBonusDamage();
		}
		damageRate_ = 1.0f;

		status->Effect(EffectTiming::BeforeAttack, StackDecreaseTiming::None);
	}
	Effect(EffectTiming::BeforeDefense, StackDecreaseTiming::None);

	damage = static_cast<int>(damage * damageRate_);
	if (damage < 0) {
		DecisionHeal(-damage, status);
	} else {
		DecisionDamage(damage, status);
	}
}

void Status::Heal(int heal, Status* status) {
	if (status) {
		status->SetBonusDamage(0);
		status->Effect(EffectTiming::BonusDamage, StackDecreaseTiming::None);
		if (status->GetBonusDamage() != 0) {
			heal -= status->GetBonusDamage();
		}
		healRate_ = 1.0f;

		status->Effect(EffectTiming::BeforeHeal, StackDecreaseTiming::None);
	}
	Effect(EffectTiming::BeforeRecovery, StackDecreaseTiming::None);

	if (heal < 0) {
		DecisionDamage(-heal, status);
	} else {
		DecisionHeal(heal, status);
	}
}

void Status::DecisionDamage(int damage, Status* status) {
	if (shield_ >= damage) {
		Effect(EffectTiming::OnDefense, StackDecreaseTiming::None);
		shield_ -= damage;
	} else {
		Effect(EffectTiming::OnDamage, StackDecreaseTiming::OnDamage);
		damage -= shield_;
		shield_ = 0;
		HP_ -= damage;
	}
	if (status) {
		status->Effect(EffectTiming::AfterAttack, StackDecreaseTiming::None);
	}
}

void Status::DecisionHeal(int heal, Status* status) {
	HP_ += heal;

	Effect(EffectTiming::OnHeal, StackDecreaseTiming::OnHeal);

	if (HP_ > maxHP_) {
		HP_ = maxHP_;
	}
	if (status) {
		status->Effect(EffectTiming::AfterHeal, StackDecreaseTiming::None);
	}
}

void Status::AddShield(int v, Status* status) { 
	status->Effect(EffectTiming::BonusShield, StackDecreaseTiming::None);
	if (status->GetBonusShield() != 0) {
		v += status->GetBonusShield();
	}
	shield_ += v;
}

void Status::AddStatusEffect(std::unique_ptr<StatusEffect> statusEffect, int stack) {
	for (int i = 0; i < statusEffects.size(); i++) {
		if (statusEffects[i]->GetStatusEffectName() == statusEffect->GetStatusEffectName()) {
			statusEffects[i]->AddStack(stack);
			return;
		}
		if (statusEffects[i]->GetStatusEffectName() == StatusEffectPair::GetStatusEffectType(statusEffect->GetStatusEffectName())) {
			if (statusEffects[i]->GetStack() > stack) {
				statusEffects[i]->AddStack(-stack);
				return;
			} else {
				stack -= statusEffects[i]->GetStack();
				statusEffects.erase(statusEffects.begin() + i);

				statusEffect->Initialize(stack, this);
				statusEffects.insert(statusEffects.begin() + i, std::move(statusEffect));
				return;
			}
		}
	}
	statusEffect->Initialize(stack, this);
	statusEffects.push_back(std::move(statusEffect));
}

void Status::ClearStatusEffect() {
	statusEffects.clear();
}

void Status::Effect(EffectTiming effectTiming, StackDecreaseTiming stackDecreaseTiming) {
	for (auto& effect : statusEffects) {
		effect->Effect(effectTiming);
		effect->DecreaseStack(stackDecreaseTiming);
	}
}
