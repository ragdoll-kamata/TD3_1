#include "Card.h"


void Card::Initialize() { 
	sprite.Initialize();

	TH = TextureManager::GetInstance()->Load("white1x1.png");
	sprite.SetTextureHandle(TH);
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize({120.0f, 160.0f});

}

void Card::Draw() { 
	sprite.Draw();
}
