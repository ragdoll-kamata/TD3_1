#include "Card.h"


void Card::Initialize() { 
	sprite.Initialize();

	TH = TextureManager::GetInstance()->Load("temporaryCard.png");
	sprite.SetTextureHandle(TH);
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize({120.0f, 160.0f});
	sprite.SetTextureRect({}, {120.0f, 160.0f});
	//sprite.SetColor({1.0f, 1.0f, 0.0f, 1.0f});
}

void Card::Draw() { 
	sprite.SetIsFlipX(isReverse);
	sprite.SetIsFlipY(isReverse);
	sprite.Draw();
}
