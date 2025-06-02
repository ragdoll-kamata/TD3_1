#include "AllReverse.h"
#include "BattleManager.h"
#include "CardManager.h"
#include "StatusEffectFactory.h"
void AllReverse::IndividualInitialize() {
	TH = TextureManager::GetInstance()->Load("card/AllReverse.png");
	sprite.SetTextureHandle(TH);
	luck = 0;
	reverseLuck = -10;
	//sprite.SetColor({0.0f, 0.0f, 0.0f, 1.0f});
	cardType = CardType::Skill;
	cardRange = CardRange::Card;
	id = 1000;
}

bool AllReverse::Effect() {

	std::vector<Card*> b = cardManager_->SelectionHand(1000, true);
	
	if (b.size() > 0) {
		for (Card* s : b) {
			if (s == nullptr) {
				break;
			}
			s->SetIsReverse(!s->GetIsReverse());
		}
		battleManager_->StatusEffectPlayer(StatusEffectFactory::CreateStatusEffect("NoDraw"), 1);
		return true;
	}

	return false;
}

bool AllReverse::ReverseEffect() {

	std::vector<Card*> b = cardManager_->SelectionHand(1000, true);

	if (b.size() > 0) {
		int i = 0;
		for (Card* s : b) {
			if (s == nullptr) {
				break;
			}
			s->SetIsReverse(!s->GetIsReverse());
			i += 5;
		}
		if (i > 0) {
			i -= 5;
		}
		battleManager_->DamagePlayer(i, nullptr);
		battleManager_->StatusEffectPlayer(StatusEffectFactory::CreateStatusEffect("NoDraw"), 1);
		return true;
	}

	return false;
}
