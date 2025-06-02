#include "Status.h"
#include "StatusEffect.h"
#include "math/MathUtility.h"
#include "StatusEffectPair.h"

using namespace MathUtility;
void Status::Initialize(Vector2 pos, Vector2 entitySize, int maxHP) {
	HP_ = maxHP;
	maxHP_ = maxHP;
	shield_ = 0;
	damageRate_ = 1.0f;
	hpS = std::make_unique<NumberSprite>();
	hpS->Initialize(pos + Vector2{0.0f, entitySize.y / 2.0f}, 0.3f);
	shieldS = std::make_unique<NumberSprite>();
	shieldS->Initialize(pos + Vector2{0.0f + 50.0f, entitySize.y / 2.0f}, 0.3f);
	hpGauge = std::make_unique<HPGauge>();
	hpGauge->Initialize(pos + Vector2{0.0f, entitySize.y / 2.0f}, maxHP_);

}

void Status::Update() {
	hpS->SetNumber(HP_);
	shieldS->SetNumber(shield_);
	hpGauge->SetHP(HP_);
	hpGauge->Update();
	int i = 0;
	for (auto& effect : statusEffects) {
		effect->SetSpritePos(hpS->GetPosition() + Vector2(-100.0f, 10.0f) + Vector2(30.0f * i, 0.0f));
		i++;
	}
	statusEffects.erase(std::remove_if(statusEffects.begin(), statusEffects.end(), [](const std::unique_ptr<StatusEffect>& effect) { return effect->GetStack() <= 0; }), statusEffects.end());
}

void Status::Draw() {
	hpGauge->Draw();
	hpS->Draw();
	if (shield_ != 0) {
		shieldS->Draw();
	}
	for (auto& effect : statusEffects) {
		effect->Draw();
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
		
		status->SetDamageRate(1.0f);

		status->Effect(EffectTiming::BeforeAttack, StackDecreaseTiming::None);
	}
	damageRate_ = 1.0f;
	Effect(EffectTiming::BeforeDefense, StackDecreaseTiming::None);

	damage = static_cast<int>(damage * damageRate_ * (status != nullptr ? status->GetDamageRate() : 1.0f));
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
		

		status->SetHealRate(1.0f);
		status->Effect(EffectTiming::BeforeHeal, StackDecreaseTiming::None);
	}
	healRate_ = 1.0f;
	Effect(EffectTiming::BeforeRecovery, StackDecreaseTiming::None);

	heal = static_cast<int>(heal * healRate_ * (status != nullptr ? status->GetHealRate() : 1.0f));
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
	if (status) {
		status->Effect(EffectTiming::BonusShield, StackDecreaseTiming::None);
		if (status->GetBonusShield() != 0) {
			v += status->GetBonusShield();
		}
	}
	shield_ += v;
}

void Status::AddStatusEffect(std::unique_ptr<StatusEffect> statusEffect, int stack, CardManager* cardManager) {
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
				statusEffect->SetCardManager(cardManager);
				statusEffects.insert(statusEffects.begin() + i, std::move(statusEffect));
				return;
			}
		}
	}
	statusEffect->Initialize(stack, this);
	statusEffect->SetCardManager(cardManager);
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
