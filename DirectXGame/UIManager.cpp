#include "UIManager.h"
#include <algorithm>
#include "CardManager.h"
#include "MapManager.h"
#include "Card.h"

using namespace MathUtility;

void UIManager::Initialize(Player* player, CardManager* cardManager, MapManager* mapManager) { 
	player_ = player;
	cardManager_ = cardManager;
	mapManager_ = mapManager;
	uiBack.Initialize();
	uiBack.SetColor({0.1f, 0.1f, 0.2f, 1.0f});
	uiBack.SetSize({1280.0f, 40.0f});
	kDeck.Initialize({1280.0f - 30.0f, 20.0f}, {25.0f, 25.0f}, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});
	map.Initialize({1280.0f - 60.0f, 20.0f}, {25.0f, 25.0f}, "white1x1.png", {1.0f, 0.0f, 1.0f, 1.0f});
	back.Initialize();
	back.SetSize({1280.0f, 720.0f});
	back.SetColor({0.0f, 0.0f, 0.0f, 0.99f});
}

void UIManager::Update() {
	float mouseWheel = static_cast<float>(Input::GetInstance()->GetWheel()) / 3.0f - prevWheel;
	prevWheel = static_cast<float>(Input::GetInstance()->GetWheel()) / 3.0f;
	scroll += mouseWheel;
	Vector2 mouse = Input::GetInstance()->GetMousePosition();
	if (!mapManager_->IsStartDirection()) {
		if (Input::GetInstance()->IsTriggerMouse(0)) {
			if (kDeck.IsOnCollision(mouse)) {
				sCard = cardManager_->GetSDeck();
				sPos.resize(sCard.size());
				float a = static_cast<float>((sCard.size() - 1) / 5);
				for (int i = 0; i < sPos.size(); i++) {
					sPos[i] = {640.0f - (160.0f * ((5 - 1) / 2.0f - (i % 5))), 380.0f + (175.0f * (a - (a - (i / 5)))) - 175.0f};
					sCard[i]->SetSpritePos(sPos[i]);
				}
				isSDeckOpen = !isSDeckOpen;
				mapManager_->SetIsMapOpen(false);
			}
			if (map.IsOnCollision(mouse)) {

				mapManager_->SetIsMapOpen(!mapManager_->GetIsMapOpen());
				isSDeckOpen = false;
				
			}
		}
	}
	if (isSDeckOpen) {
		float a = static_cast<float>((sCard.size() - 1) / 5);

		float sc = std::clamp<float>(scroll, std::min<float>(-175.0f * (a - 2), 0), 0);
		scroll = Lerp(scroll, sc, 0.4f);
		for (int i = 0; i < sCard.size(); i++) {
			sCard[i]->SetSpritePos(Vector2Lerp(sCard[i]->GetSpritePos(),{sPos[i].x, sPos[i].y + scroll},0.1f));
		}
	} else {
		scroll = 0;
	}
}

void UIManager::Draw() { 
	if (isSDeckOpen) {
		back.Draw();
		for (Card* card : sCard) {
			card->Draw();
		}
	}
	uiBack.Draw();
	kDeck.Draw();
	map.Draw();
}
