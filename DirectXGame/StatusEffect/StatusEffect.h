#pragma once
#include "EffectTiming.h"
#include "StackDecreaseTiming.h"
#include "Status.h"
#include <string>

class BattleManager;

class StatusEffect {
public:
	 
	virtual ~StatusEffect() = default;
	void Initialize(int stack, Status* status);

	virtual void PeculiarInitialize() = 0;

	void Effect(EffectTiming effectTiming);

	virtual void ApplyEffect() = 0;

	void DecreaseStack(StackDecreaseTiming timing);
	void SetBattleManager(BattleManager* battleManager) { battleManager_ = battleManager; }


	void AddStack(int stack) { stack_ += stack; }
	int GetStack() const { return stack_; }

	void SetStatusEffectName(std::string statusEffectName) { statusEffectName_ = statusEffectName; }
	std::string GetStatusEffectName() const { return statusEffectName_; }



protected:
	int stack_;
	BattleManager* battleManager_;
	Status* status_;
	EffectTiming effectTiming_;
	StackDecreaseTiming stackDecreaseTiming_;

	std::string statusEffectName_;
};
