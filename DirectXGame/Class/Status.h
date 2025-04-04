#pragma once
#include <vector>
#include <memory>
#include "EffectTiming.h"
#include "StackDecreaseTiming.h"
#include "NumberSprite.h"
class StatusEffect;
class Status {
public:

	void Initialize(Vector2 pos, Vector2 size, int maxHP);
	
	void Update();

	void Draw();
	void AddMaxHP(int v) { maxHP_ += v; }
	int GetMaxHP() const { return maxHP_; }

	int GetHP() const { return HP_; }

	int GetShield() const { return shield_; }
	
	void ClearShield() { shield_ = 0; }

	void SetDamageRate(float rate) { damageRate_ = rate; }

	float GetDamageRate() const { return damageRate_; }

	void SetHealRate(float rate) { healRate_ = rate; }
	float GetHealRate() const { return healRate_; }

	void ApplyDirectDamage(int damage);

	void Damage(int damage, Status* status);

	void Heal(int heal, Status* status);

private:
	void DecisionDamage(int damage, Status* status);

	void DecisionHeal(int heal, Status* status);

public:

	void AddShield(int v, Status* status);

	void AddStatusEffect(std::unique_ptr<StatusEffect> statusEffect, int stack);

	void ClearStatusEffect();

	void Effect(EffectTiming effectTiming, StackDecreaseTiming stackDecreaseTiming);

	void SetBonusDamage(int v) { BonusDamage = v; }
	int GetBonusDamage() const { return BonusDamage; }

	void SetBonusShield(int v) { BonusShield = v; }
	int GetBonusShield() const { return BonusShield; }


private:
	int HP_;
	int maxHP_;
	int shield_;

	float damageRate_ ;
	float healRate_;

	std::vector<std::unique_ptr<StatusEffect>> statusEffects;
	NumberSprite hpS;
	NumberSprite shieldS;

	int BonusDamage = 0;
	int BonusShield = 0;
};
