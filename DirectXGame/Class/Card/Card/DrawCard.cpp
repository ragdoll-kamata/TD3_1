#include "DrawCard.h"
#include "CardManager.h"

void DrawCard::IndividualInitialize() {
	TH = TextureManager::GetInstance()->Load("card/DrawCard.png");
	sprite.SetTextureHandle(TH);
	luck = 2;
	reverseLuck = -4;
	cardType = CardType::Skill;
	cardRange = CardRange::Self;
	id = 12;
	//sprite.SetColor({1.0f, 0.5f, 0.0f, 1.0f});
}

bool DrawCard::Effect() {
	cardManager_->CardDraw(2);
	return true;
}

bool DrawCard::ReverseEffect() { 
	cardManager_->CardDraw(2, 2, true);
	return true;
}
