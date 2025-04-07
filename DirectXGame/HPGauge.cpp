#include "HPGauge.h"
using namespace MathUtility;
void HPGauge::Initialize(Vector2 pos, int maxHP) {
	maxHP_ = maxHP;
	sprite.Initialize();
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize({200.0f, 20.0f});
	sprite.SetPosition(pos);
	sprite.SetColor({1.0f, 0.0f, 0.0f, 1.0f});

	sprite2.Initialize();
	sprite2.SetAnchorPoint({0.0f, 0.5f});
	sprite2.SetSize({200.0f, 20.0f});
	sprite2.SetPosition(pos - Vector2(100.0f, 0.0f));
	sprite2.SetColor({0.0f, 1.0f, 0.0f, 1.0f});

}

void HPGauge::Update() {
	float t = static_cast<float>(HP_) / static_cast<float>(maxHP_);
	sprite2.SetSize({200.0f * t, 20.0f});


}

void HPGauge::Draw() {
	sprite.Draw();
	sprite2.Draw();
}