#include "Reverse.h"
#include "CardManager.h"
void Reverse::IndividualInitialize() {
	luck = 0;
	reverseLuck = -2;
	sprite.SetColor({1.0f, 0.0f, 1.0f, 1.0f});
	cardType = CardType::Skill;
	cardRange = CardRange::Card;
	id = 4;
}

bool Reverse::Effect() { 
	
	std::vector<Card*> a = cardManager_->SelectionHand(2, false);

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

bool Reverse::ReverseEffect() {
	std::vector<Card*> a = cardManager_->SelectionHand(2, true);

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
