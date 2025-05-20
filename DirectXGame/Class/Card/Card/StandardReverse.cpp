#include "StandardReverse.h"
#include "CardManager.h"

void StandardReverse::IndividualInitialize() {
	luck = 0;
	reverseLuck = -1;
	sprite.SetColor({1.0f, 0.2f, 1.0f, 1.0f});
	cardType = CardType::Skill;
	cardRange = CardRange::Card;
	id = 3;
}

bool StandardReverse::Effect() {
	std::vector<Card*> a = cardManager_->SelectionHand(1, false);
	int i = 0;
	if (a.size() > 0) {
		for (Card* s : a) {
			if (s == nullptr) {
				break;
			}
			i++;
			s->SetIsReverse(!s->GetIsReverse());
		}
		return true;
	}

	return false;
}

bool StandardReverse::ReverseEffect() {
	std::vector<Card*> a = cardManager_->SelectionHand(1, true);
	int i = 0;
	if (a.size() > 0) {
		for (Card* s : a) {
			if (s == nullptr) {
				break;
			}
			i++;
			s->SetIsReverse(!s->GetIsReverse());
		}
		i -= 1;
		if (i < 0) {
			cardManager_->CardDraw(-i);
		}
		return true;
	}

	return false;
}
