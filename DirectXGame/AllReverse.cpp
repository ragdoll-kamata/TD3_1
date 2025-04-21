#include "AllReverse.h"
#include "CardManager.h"
#include "BattleManager.h"
void AllReverse::IndividualInitialize() {
	luck = 0;
	reverseLuck = -10;
	sprite.SetColor({0.0f, 0.0f, 0.0f, 1.0f});
	cardType = CardType::Skill;
	cardRange = CardRange::Card;
	id = 1000;
}

bool AllReverse::Effect() {
	std::vector<Card*> a = cardManager_->SelectionHand(99, true);
	battleManager_->DamagePlayer(5, nullptr);
	if (a.size() > 0) {
		for (Card* s : a) {
			if (s == nullptr) {
				break;
			}
			s->SetIsReverse(!s->GetIsReverse());
		}
		return true;
	}
	return false;
}

bool AllReverse::ReverseEffect() {
	std::vector<Card*> a = cardManager_->SelectionHand(99, true);

	if (a.size() > 0) {
		int i = 0;
		for (Card* s : a) {
			if (s == nullptr) {
				break;
			}
			s->SetIsReverse(!s->GetIsReverse());
			i += 5;
		}
		battleManager_->DamagePlayer(i, nullptr);
		return true;
	}
	return false;
}
