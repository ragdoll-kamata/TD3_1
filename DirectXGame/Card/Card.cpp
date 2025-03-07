#include "Card.h"
#include <algorithm>

void Card::Initialize() {
	sprite.Initialize();

	TH = TextureManager::GetInstance()->Load("temporaryCard.png");
	sprite.SetTextureHandle(TH);
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize({120.0f, 160.0f});
	sprite.SetTextureRect({}, {120.0f, 160.0f});

	IndividualInitialize();
}

void Card::Draw() { 
	sprite.SetIsFlipX(isReverse);
	sprite.SetIsFlipY(isReverse);
	sprite.Draw();
}

bool Card::IsOnCollision(Vector2 pos) { 
	
	Vector2 hPos{
	    std::clamp(pos.x, sprite.GetPosition().x - 60.0f, sprite.GetPosition().x + 60.0f),
	    std::clamp(pos.y, sprite.GetPosition().y - 80.0f, sprite.GetPosition().y + 80.0f),
	};

	hPos.x -= pos.x;
	hPos.y -= pos.y;
	float len = MathUtility::Length(hPos);
	if (len <= 0.0f) {
		return true;
	}
	return false; 
}
