#include "StatusEffectFactory.h"
#include "Poison.h"
#include "Regeneration.h"
#include "Fragility.h"
#include "AntiFragile.h"
#include "AurOfDeath.h"
#include "AuraOfLife.h"
std::unique_ptr<StatusEffect> StatusEffectFactory::CreateStatusEffect(std::string statusEffectName) { 
	uint32_t th = 0;
	if (statusEffectName == "Poison") {
		th = TextureManager::GetInstance()->Load("UI/poison.png");
		std::unique_ptr<StatusEffect> statusEffect = std::make_unique<Poison>();
		statusEffect->SetStatusEffectName("Poison");
		statusEffect->SetSpriteTextureHandle(th);
		return std::move(statusEffect);
	}
	if (statusEffectName == "Regeneration") {
		th = TextureManager::GetInstance()->Load("UI/regeneration.png");
		std::unique_ptr<StatusEffect> statusEffect = std::make_unique<Regeneration>();
		statusEffect->SetStatusEffectName("Regeneration");
		statusEffect->SetSpriteTextureHandle(th);
		return std::move(statusEffect);
	}
	if (statusEffectName == "Fragility") {
		th = TextureManager::GetInstance()->Load("UI/fragility.png");
		std::unique_ptr<StatusEffect> statusEffect = std::make_unique<Fragility>();
		statusEffect->SetStatusEffectName("Fragility");
		statusEffect->SetSpriteTextureHandle(th);
		return std::move(statusEffect);
	}
	if (statusEffectName == "AntiFragile") {
		th = TextureManager::GetInstance()->Load("UI/antifragile.png");
		std::unique_ptr<StatusEffect> statusEffect = std::make_unique<AntiFragile>();
		statusEffect->SetStatusEffectName("AntiFragile");
		statusEffect->SetSpriteTextureHandle(th);
		return std::move(statusEffect);
	}
	if (statusEffectName == "AuraOfDeath") {
		th = TextureManager::GetInstance()->Load("UI/damageIncrease.png");
		std::unique_ptr<StatusEffect> statusEffect = std::make_unique<AurOfDeath>();
		statusEffect->SetStatusEffectName("AurOfDeath");
		statusEffect->SetSpriteTextureHandle(th);
		return std::move(statusEffect);
	}
	if (statusEffectName == "AuraOfLife") {
		th = TextureManager::GetInstance()->Load("UI/auraOfLife.png");
		std::unique_ptr<StatusEffect> statusEffect = std::make_unique<AuraOfLife>();
		statusEffect->SetStatusEffectName("AuraOfLife");
		statusEffect->SetSpriteTextureHandle(th);
		return std::move(statusEffect);
	}
	return nullptr;


}
