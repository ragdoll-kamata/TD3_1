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
	sprite.SetColor({0.9f, 0.9f, 0.9f, 1.0f});

	sprite2.Initialize();
	TH = TextureManager::GetInstance()->Load("card/cardBottom.png");
	sprite2.SetTextureHandle(TH);
	sprite2.SetAnchorPoint({0.5f, 0.5f});
	sprite2.SetSize({120.0f, 160.0f});
	sprite2.SetTextureRect({}, {120.0f, 160.0f});
	
	IndividualInitialize();
	
	number.Initialize({}, 0.5f, {0.0f, 0.0f});
	number.SetNumber(luck);
	nextNumberRotate = 0.0f;

	number2.Initialize({}, 0.5f, {0.0f, 0.0f});
	number2.SetNumber(reverseLuck);
	nextNumber2Rotate = PI;
	number2.SetRotate(nextNumber2Rotate);
}

void Card::SetSpritePos(const Vector2& pos) {
	sprite.SetPosition(pos);
	sprite2.SetPosition(pos);
	number.SetPosition(pos);
	number2.SetPosition(pos);
}

void Card::Updata() {
	if (isReverse != prevIsReverse) {
		prevIsReverse = isReverse;
		nextRotate += PI;
		nextNumberRotate += PI;
		nextNumber2Rotate += PI;
	}
	sprite.SetSize({120.0f * size_, 160.0f * size_});
	sprite2.SetSize({120.0f * size_, 160.0f * size_});
	rotate = Lerp(rotate, nextRotate, 0.2f);
	sprite.SetRotation(rotate);
	sprite2.SetRotation(rotate);

	Vector2 ppp = {
	    -60.0f * size_,
	    -80.0f * size_,
	};
	float r = Lerp(number.GetRotate(), nextNumberRotate, 0.2f);
	Vector2 sss = {
	    ppp.x * std::cos(r) - ppp.y * std::sin(r),
	    ppp.x * std::sin(r) + ppp.y * std::cos(r),
	};
	number.SetPosition(sprite.GetPosition() + sss);
	number.SetRotate(r);

	ppp = {
	    -60.0f * size_,
	    -80.0f * size_,
	};
	r = Lerp(number2.GetRotate(), nextNumber2Rotate, 0.2f);
	sss = {
	    ppp.x * std::cos(r) - ppp.y * std::sin(r),
	    ppp.x * std::sin(r) + ppp.y * std::cos(r),
	};
	number2.SetRotate(r);
	number2.SetPosition(sprite.GetPosition() + sss);


}

void Card::Draw() { 
	sprite.SetSize({120.0f * size_, 160.0f * size_});
	sprite.Draw();
	sprite2.Draw();
	number.Draw();
	number2.Draw();
}

bool Card::StartEffect() { 
	if (isReverse) {
		return ReverseEffect();
	} else {
		return Effect();
	}
}

void Card::KSetIsReverse(bool is) {
	if (is != prevIsReverse) {
		isReverse = is;
		prevIsReverse = isReverse;
		nextRotate += PI;
		rotate += PI;
		nextNumberRotate += PI;
		nextNumber2Rotate += PI;
		number.SetRotate(nextNumberRotate);
		number2.SetRotate(nextNumber2Rotate);
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
