#include "Card.h"
#include <algorithm>

using namespace MathUtility;

void Card::Initialize() {
	sprite.Initialize();

	TH = TextureManager::GetInstance()->Load("temporaryCard.png");
	sprite.SetTextureHandle(TH);
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize({120.0f, 160.0f});
	sprite.SetTextureRect({}, {120.0f, 160.0f});

	IndividualInitialize();
}

void Card::Updata() {
	if (isReverse != prevIsReverse) {
		prevIsReverse = isReverse;
		nextRotate += PI;
	}
	sprite.SetSize({120.0f * size_, 160.0f * size_});
	rotate = Lerp(rotate, nextRotate, 0.2f);
	sprite.SetRotation(rotate);
}

void Card::Draw() { 
	sprite.SetSize({120.0f * size_, 160.0f * size_});
	sprite.Draw();
}

void Card::KSetIsReverse(bool is) {
	if (is != prevIsReverse) {
		isReverse = is;
		prevIsReverse = isReverse;
		nextRotate += PI;
		rotate += PI;
	}
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
