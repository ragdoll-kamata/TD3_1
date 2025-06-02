#include "Reverse.h"
#include "CardManager.h"
void Reverse::IndividualInitialize() {
	TH = TextureManager::GetInstance()->Load("card/Reverse.png");
	sprite.SetTextureHandle(TH);
	luck = 0;
	reverseLuck = -2;
	//sprite.SetColor({1.0f, 0.0f, 1.0f, 1.0f});
	cardType = CardType::Skill;
	cardRange = CardRange::Card;
	id = 14;
}

bool Reverse::Effect() { 
	std::vector<Card*> a = cardManager_->SelectionHand(2, false);
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

bool Reverse::ReverseEffect() {
	std::vector<Card*> a = cardManager_->SelectionHand(2, true);
	int i = 0;
	if (a.size() > 0) {
		for (Card* s : a) {
			if (s == nullptr) {
				break;
			}
			i++;
			s->SetIsReverse(!s->GetIsReverse());
		}
		i -= 2;
		if (i < 0) {
			cardManager_->CardDraw(-i);
		}
		return true;
	}

	return false;
}
