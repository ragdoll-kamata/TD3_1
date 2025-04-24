#include "NumberSprite.h"
using namespace MathUtility;
void NumberSprite::Initialize(Vector2 pos, float size, const Vector2 anchor) {
	pos_ = pos;
	size_ = size;
	anchor_ = anchor;
}

void NumberSprite::Draw() {
	for (Sprite s : sprite) {
		s.Draw();
	}
}

void NumberSprite::SetPosition(Vector2 pos) { 
	pos_ = pos;
	SpritePos();
}

void NumberSprite::SetNumber(int num) {
	is = false;
	if (num < 0) {
		is = true;
	}
	sprite.clear();

	int index = num <= 0 ? -num : num;

	Number(index);
	SpritePos();

	
}

int NumberSprite::Number(int num, int num2) {
	int i = num;
	if (num >= num2 * 10) {
		i = Number(num, num2 * 10);
		i = i / num2;
	} else {
		i = num / num2;
	}
	sprite.push_back(CreateSprite(i));
	return num % num2;
}

Sprite NumberSprite::CreateSprite(int num) {
	Sprite s;
	s.Initialize();

	TH = TextureManager::GetInstance()->Load("number.png");
	s.SetTextureHandle(TH);
	s.SetAnchorPoint(anchor_);
	s.SetSize(cSize * size_);
	s.SetTextureRect({cSize.x * num, 0.0f}, cSize);
	s.SetRotation(rotate_);
	if (is) {
		s.SetColor({0.9f, 0.1f, 0.1f, 1.0f});
	} else {
		s.SetColor({0.7f, 0.7f, 0.7f, 1.0f});
	}
	return s;
}

void NumberSprite::SpritePos() {
	Vector2 sss;
	for (int i = 0; i < sprite.size(); i++) {
		sss = {-((cSize.x * size_) * ((sprite.size() - 1) * anchor_.x - i)), 0.0f};
		sss = {
		    sss.x * std::cos(rotate_) - sss.y * std::sin(rotate_),
		    sss.x * std::sin(rotate_) + sss.y * std::cos(rotate_),
		};
		Vector2 pos__ = {pos_.x + sss.x, pos_.y + sss.y};
		sprite[i].SetAnchorPoint(anchor_);
		sprite[i].SetPosition(pos__);
		sprite[i].SetRotation(rotate_);
	}
}
