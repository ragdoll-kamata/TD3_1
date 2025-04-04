#include "StatusEffectFactory.h"
#include "Poison.h"
#include "Regeneration.h"
#include "Fragility.h"
#include "AntiFragile.h"
#include "Strength.h"
std::unique_ptr<StatusEffect> StatusEffectFactory::CreateStatusEffect(std::string statusEffectName) { 

	if (statusEffectName == "Poison") {
		std::unique_ptr<StatusEffect> statusEffect = std::make_unique<Poison>();
		statusEffect->SetStatusEffectName("Poison");
		return std::move(statusEffect);
	}
	if (statusEffectName == "Regeneration") {
		std::unique_ptr<StatusEffect> statusEffect = std::make_unique<Regeneration>();
		statusEffect->SetStatusEffectName("Regeneration");
		return std::move(statusEffect);
	}
	if (statusEffectName == "Fragility") {
		std::unique_ptr<StatusEffect> statusEffect = std::make_unique<Fragility>();
		statusEffect->SetStatusEffectName("Fragility");
		return std::move(statusEffect);
	}
	if (statusEffectName == "AntiFragile") {
		std::unique_ptr<StatusEffect> statusEffect = std::make_unique<AntiFragile>();
		statusEffect->SetStatusEffectName("AntiFragile");
		return std::move(statusEffect);
	}
	if (statusEffectName == "Strength") {
		std::unique_ptr<StatusEffect> statusEffect = std::make_unique<Strength>();
		statusEffect->SetStatusEffectName("Strength");
		return std::move(statusEffect);
	}
	return nullptr;


}
