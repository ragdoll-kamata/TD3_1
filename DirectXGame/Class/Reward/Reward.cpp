#include "Reward.h"
#include <algorithm>

void Reward::Initialize(CardManager* cardManager, RelicManager* relicManager) {
	cardManager;
	relicManager;
	sp.Initialize();
	sp.SetSize({160.0f, 40.0f});
	sp.SetAnchorPoint({0.5f, 0.5f});
}

void Reward::Update() {
	if (!isU && !isR) {
		Vector2 mousePos = Input::GetInstance()->GetMousePosition();
		Vector2 a = sp.GetPosition();
		Vector2 hPos{
		    std::clamp(mousePos.x, a.x - 80.0f, a.x + 80.0f),
		    std::clamp(mousePos.y, a.y - 20.0f, a.y + 20.0f),
		};
		hPos.x -= mousePos.x;
		hPos.y -= mousePos.y;
		float len = MathUtility::Length(hPos);
		if (len <= 0.0f) {
			if (Input::GetInstance()->IsTriggerMouse(0)) {
				isR = true;
			}
		}
	}
}

void Reward::Draw() { sp.Draw(); }

void Reward::CardDraw() {}
