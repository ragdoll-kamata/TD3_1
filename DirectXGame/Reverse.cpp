#include "Reverse.h"
#include "CardManager.h"
void Reverse::Initialize() {
	Card::Initialize();
	luck = 0;
	rverseLuck = 0;
	sprite.SetColor({1.0f, 0.0f, 1.0f, 1.0f});
	cardType = CardType::Skill;
	cardRange = CardRange::Card;
	id = 4;
}

bool Reverse::Effect() { 
	
	std::vector<Card*> a = cardManager_->SelectionHand(2);

	if (a.size() > 0) {
		for (Card* s : a) {
			s->SetIsReverse(!s->GetIsReverse());
		}
		return true;
	} 
	return false; 
}

bool Reverse::ReverseEffect() { return false; }
