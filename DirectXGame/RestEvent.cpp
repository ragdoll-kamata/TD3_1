#include "RestEvent.h"


void RestEvent::Initialize(RewardManager* rewardManager) {
	Event::Initialize(rewardManager);
	back.Initialize();
	back.SetSize({1280.0f, 720.0f});
	back.SetColor({0.0f, 0.0f, 0.0f, 0.5f});
	restButton = std::make_unique<Button>();
	restButton->Initialize({530.0f, 360.0f}, {200.0f, 100.0f}, "white1x1.png", {1.0f, 5.0f, 0.0f, 1.0f});
	disCardButton = std::make_unique<Button>();
	disCardButton->Initialize({750.0f, 360.0f}, {200.0f, 100.0f}, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});
	disCardCancelButton = std::make_unique<Button>();
	disCardCancelButton->Initialize({1130.0f, 600.0f}, {150.0f, 50.0f}, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});
	
}

void RestEvent::Update() {
	if (is) {
		float mouseWheel = static_cast<float>(Input::GetInstance()->GetWheel()) / 3.0f - prevWheel;
		prevWheel = static_cast<float>(Input::GetInstance()->GetWheel()) / 3.0f;
		scroll += mouseWheel;
		
		float a = static_cast<float>((sCard.size() - 1) / 5);

		float sc = std::clamp<float>(scroll, std::min<float>(-175.0f * (a - 2), 0), 0);
		scroll = MathUtility::Lerp(scroll, sc, 0.4f);
		for (int i = 0; i < sCard.size(); i++) {
			sCard[i]->SetSpritePos(MathUtility::Vector2Lerp(sCard[i]->GetSpritePos(), {sPos[i].x, sPos[i].y + scroll}, 0.1f));
			sCard[i]->Updata();
		}
	
		if (Input::GetInstance()->IsTriggerMouse(0)) {
			Vector2 mousePos = Input::GetInstance()->GetMousePosition();
			for (auto& card : sCard) {
				if (card->IsOnCollision(mousePos)) {
					cardManager_->DeleteSDeckCard(card);
					isEnd = true; // イベント終了フラグを立てる
				}
			}
			if (disCardCancelButton->IsOnCollision(mousePos)) {
				is = false;
			}
		}
		
	} else {

		if (Input::GetInstance()->IsTriggerMouse(0)) {
			Vector2 mousePos = Input::GetInstance()->GetMousePosition();
			if (restButton->IsOnCollision(mousePos)) {
				player_->Rest();
				isEnd = true; // イベント終了フラグを立てる
			}
			if (disCardButton->IsOnCollision(mousePos)) {
				sCard = cardManager_->GetSDeck();
				sPos.resize(sCard.size());
				float a = static_cast<float>((sCard.size() - 1) / 5);
				for (int i = 0; i < sCard.size(); i++) {
					sPos[i] = {640.0f - (160.0f * ((5 - 1) / 2.0f - (i % 5))), 380.0f + (175.0f * (a - (a - (i / 5)))) - 175.0f};
					sCard[i]->SetSpritePos({640.0f - (160.0f * ((5 - 1) / 2.0f - (i % 5))), 380.0f + (175.0f * (a - (a - (i / 5)))) - 175.0f});
					sCard[i]->Updata();
				}
				is = true;
				scroll = 0.0f;
			}
		}
	}
}

void RestEvent::Draw() {
	restButton->Draw();
	disCardButton->Draw();
	if (is) {
		back.Draw();
		disCardCancelButton->Draw();
		for (auto& card : sCard) {
			card->Draw();
		}
	}

}
