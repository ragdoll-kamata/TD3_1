#pragma once
#include <KamataEngine.h>
#include "EffectTiming.h"
#include "StackDecreaseTiming.h"
#include "NumberSprite.h"
#include "Status.h"
#include <string>
#include <memory>

class BattleManager;

class StatusEffect {
public:
	 
	virtual ~StatusEffect() = default;
	void Initialize(int stack, Status* status);

	virtual void PeculiarInitialize() = 0;

	void Draw();

	void Effect(EffectTiming effectTiming);

	virtual void ApplyEffect() = 0;

	void DecreaseStack(StackDecreaseTiming timing);
	void SetBattleManager(BattleManager* battleManager) { battleManager_ = battleManager; }


	void AddStack(int stack);
	int GetStack() const { return stack_; }

	void SetStatusEffectName(std::string statusEffectName) { statusEffectName_ = statusEffectName; }
	std::string GetStatusEffectName() const { return statusEffectName_; }

	void SetSpritePos(Vector2 pos);

	void SetSpriteTextureHandle(uint32_t th) { sprite_.SetTextureHandle(th); }

protected:
	int stack_;
	BattleManager* battleManager_;
	Status* status_;
	EffectTiming effectTiming_;
	StackDecreaseTiming stackDecreaseTiming_;

	std::string statusEffectName_;

	KamataEngine::Sprite sprite_;

	std::unique_ptr<NumberSprite> numberSprite_;
};
