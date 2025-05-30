#include "Button.h"
#include <algorithm>
using namespace MathUtility;
void Button::Initialize(const Vector2& pos, const Vector2& size, std::string name, Vector4 color) {
	TH = TextureManager::GetInstance()->Load(name);

	sprite.Initialize();
	sprite.SetTextureHandle(TH);
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize(size);
	sprite.SetColor(color);
	sprite.SetPosition(pos);
	halfSize = size;
	halfSize /= 2.0f;
}

void Button::Draw() { sprite.Draw(); }

bool Button::IsOnCollision(Vector2 pos) { 
	
	Vector2 hPos{
	    std::clamp(pos.x, sprite.GetPosition().x - halfSize.x, sprite.GetPosition().x + halfSize.x),
	    std::clamp(pos.y, sprite.GetPosition().y - halfSize.y, sprite.GetPosition().y + halfSize.y),
	};

	hPos.x -= pos.x;
	hPos.y -= pos.y;
	float len = MathUtility::Length(hPos);
	if (len <= 0.0f) {
		return true;
	}
	return false;
}

void Button::SetTextureRect(Vector2 rect) { sprite.SetTextureRect({}, rect); }
