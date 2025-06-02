#include "VeryCareful.h"
#include "CardManager.h"

void VeryCareful::IndividualInitialize() {
	TH = TextureManager::GetInstance()->Load("card/VeryCareful.png");
	sprite.SetTextureHandle(TH);
	luck = 0;
	reverseLuck = 0;
	//sprite.SetColor({0.5f, 0.5f, 0.5f, 1.0f});
	cardType = CardType::Skill;
	cardRange = CardRange::Card;
	id = 101;
}

bool VeryCareful::Effect() {
	if (!isSS) {
		cardManager_->CardDraw(1);
		isSS = true;
	}

	std::vector<Card*> a = cardManager_->SelectionHand(1, true);

	if (a.size() > 0) {
		for (Card* s : a) {
			if (s == nullptr) {
				break;
			}
			cardManager_->CardLocationMove(s, CardLocation::Cemetery);
			
		}
		isSS = false;
		return true;
	}
	return false;
}

bool VeryCareful::ReverseEffect() {
	std::vector<Card*> a = cardManager_->SelectionHand(1, true);

	if (a.size() > 0) {
		for (Card* s : a) {
			if (s == nullptr) {
				break;
			}
			cardManager_->CardLocationMove(s, CardLocation::Cemetery);
		}
		cardManager_->CardDraw(1);
		return true;
	}
	return false;
}
