#include "CardManager.h"
#include "CollisionDetection.h"
#include <algorithm>
using namespace CollisionDetection;
using namespace MathUtility;
void CardManager::Initialize() {
	std::random_device rd; // 乱数の種
	g.seed(rd());

	sDeck.push_back(std::make_unique<StandardAtack>());
	sDeck.push_back(std::make_unique<StandardAtack>());
	sDeck.push_back(std::make_unique<StandardAtack>());
	sDeck.push_back(std::make_unique<StandardAtack>());
	sDeck.push_back(std::make_unique<StandardAtack>());
	sDeck.push_back(std::make_unique<StandardShield>());
	sDeck.push_back(std::make_unique<StandardShield>());
	sDeck.push_back(std::make_unique<StandardShield>());
	sDeck.push_back(std::make_unique<StandardShield>());
	sDeck.push_back(std::make_unique<StandardShield>());


	for (int i = 0; i < sDeck.size(); i++) {
		sDeck[i]->Initialize();
	}

	StartBattle();

	turnEndButtonTH = TextureManager::GetInstance()->Load("white1x1.png");
	turnEndButton.Initialize();
	turnEndButton.SetTextureHandle(turnEndButtonTH);
	turnEndButton.SetAnchorPoint({0.5f, 0.5f});
	turnEndButton.SetSize({160.0f, 40.0f});
	turnEndButton.SetColor({1.0f, 0.0f, 0.0f, 1.0f});
	turnEndButton.SetPosition(turnEndButtonPos);

	allReverseYssButton.Initialize();
	allReverseYssButton.SetTextureHandle(turnEndButtonTH);
	allReverseYssButton.SetAnchorPoint({0.5f, 0.5f});
	allReverseYssButton.SetSize({allReverseButtonHalfSize.x * 2.0f, allReverseButtonHalfSize.y * 2.0f});
	allReverseYssButton.SetColor({0.0f, 1.0f, 0.0f, 1.0f});
	allReverseYssButton.SetPosition(allReverseYssButtonPos);

	allReverseNoButton.Initialize();
	allReverseNoButton.SetTextureHandle(turnEndButtonTH);
	allReverseNoButton.SetAnchorPoint({0.5f, 0.5f});
	allReverseNoButton.SetSize({allReverseButtonHalfSize.x * 2.0f, allReverseButtonHalfSize.y * 2.0f});
	allReverseNoButton.SetColor({1.0f, 0.0f, 0.0f, 1.0f});
	allReverseNoButton.SetPosition(allReverseNoButtonPos);
}

void CardManager::BattleUpdata() { 
	mBattlePhase[battlePhase]();
}

void CardManager::DrawBattle() {
	if (isReverseButton) {
		allReverseYssButton.Draw();
		allReverseNoButton.Draw();
	}


	turnEndButton.Draw();
	for (int i = 0; i < handCard.size(); i++) {
		handCard[i]->Draw();
	}
}

void CardManager::StartMainTurn() {
	if (drawIndex < 5) {
		drawTimer++;

		if (drawTimer >= kDrawTimer) {
			drawTimer = 0;
			drawIndex++;
			CardDraw();
			for (int i = 0; i < handCard.size(); i++) {
				Vector2 pos = {640.0f - (121.0f * ((handCard.size() - 1) / 2.0f - i)), 600.0f};
				handCard[i]->SetSpritePos(pos);
			}
		}
	} else {
		isReverseButton = true;
		Vector2 mousePos = Input::GetInstance()->GetMousePosition();
		if (Input::GetInstance()->IsTriggerMouse(0)) {
			if (handLack >= 0) {
				Vector2 hPos{
				    std::clamp(mousePos.x, allReverseYssButtonPos.x - allReverseButtonHalfSize.x, allReverseYssButtonPos.x + allReverseButtonHalfSize.x),
				    std::clamp(mousePos.y, allReverseYssButtonPos.y - allReverseButtonHalfSize.y, allReverseYssButtonPos.y + allReverseButtonHalfSize.y),
				};

				hPos.x -= mousePos.x;
				hPos.y -= mousePos.y;
				float len = Length(hPos);
				if (len <= 0.0f) {
					isReverseButton = false;
					battlePhase = BattlePhase::MainTurn;
					drawIndex = 0;
					for (int i = 0; i < handCard.size(); i++) {
						handCard[i]->SetIsReverse(!handCard[i]->GetIsReverse());
					}
				}

				hPos = {
				    std::clamp(mousePos.x, allReverseNoButtonPos.x - allReverseButtonHalfSize.x, allReverseNoButtonPos.x + allReverseButtonHalfSize.x),
				    std::clamp(mousePos.y, allReverseNoButtonPos.y - allReverseButtonHalfSize.y, allReverseNoButtonPos.y + allReverseButtonHalfSize.y),
				};

				hPos.x -= mousePos.x;
				hPos.y -= mousePos.y;
				len = Length(hPos);
				if (len <= 0.0f) {
					isReverseButton = false;
					battlePhase = BattlePhase::MainTurn;
					drawIndex = 0;
				}
			}
		}
	}

}

void CardManager::MainTurn() {
	Vector2 mousePos = Input::GetInstance()->GetMousePosition();
	AllHandLack();
	for (int i = 0; i < handCard.size(); i++) {
		Vector2 pos = {640.0f - (121.0f * ((handCard.size() - 1) / 2.0f - i)), 600.0f};

		handCard[i]->SetSpritePos(pos);

		Vector2 hPos{
		    std::clamp(mousePos.x, pos.x - 60.0f, pos.x + 60.0f),
		    std::clamp(mousePos.y, pos.y - 80.0f, pos.y + 80.0f),
		};

		hPos.x -= mousePos.x;
		hPos.y -= mousePos.y;
		float len = Length(hPos);
		if (len <= 0.0f) {
			if (Input::GetInstance()->IsTriggerMouse(0)) {
				holdH = i;
				isHold = true;
				handCard[i]->SetSpritePos(mousePos);
			}
		}
		if (holdH == i) {
			if (isHold) {
				if (Input::GetInstance()->IsPressMouse(0)) {
					handCard[i]->SetSpritePos(mousePos);
				} else {
					if (mousePos.y <= 360.0f) {
						execution.push_back(std::move(handCard[holdH])); // ムーブ
						handCard.erase(handCard.begin() + holdH);        // 元のリストから削除
					}

					isHold = false;
				}
			}
		}
	}

	if (execution.size()) {
		cemetery.push_back(std::move(execution[0])); // ムーブ
		execution.erase(execution.begin());       // 元のリストから削除
	}

	if (Input::GetInstance()->IsTriggerMouse(0)) {
		if (handLack >= 0) {
			Vector2 hPos{
			    std::clamp(mousePos.x, turnEndButtonPos.x - 80.0f, turnEndButtonPos.x + 80.0f),
			    std::clamp(mousePos.y, turnEndButtonPos.y - 20.0f, turnEndButtonPos.y + 20.0f),
			};

			hPos.x -= mousePos.x;
			hPos.y -= mousePos.y;
			float len = Length(hPos);
			if (len <= 0.0f) {
				battlePhase = BattlePhase::EndMainTurn;
			}
		}
	}
}

void CardManager::EndMainTurn() {
	while (handCard.size() > 0) {
		// handCard から cemetery にカードを移動
		cemetery.push_back(std::move(handCard.back())); // 一番最後のカードを移動
		handCard.pop_back();                            // 移動後に元のデッキから削除
	}
	battlePhase = BattlePhase::StartMainTurn;
}

void CardManager::StartBattle() {
	//デッキ生成
	for (const auto& card : sDeck) {
		deck.push_back(card->clone()); // クローンを作る
	}
	DeckShuffle();
}

void CardManager::EndBattle() {
	while (handCard.size() > 0) {
		handCard.pop_back();
	}
	while (deck.size() > 0) {
		deck.pop_back();
	}
	while (cemetery.size() > 0) {
		cemetery.pop_back();
	}

}

void CardManager::EnemyTurn() {}

void CardManager::CardDraw() {
	if (deck.size() <= 0) {
		DeckRefresh();
	}
	// deck から handCard にカードを移動
	handCard.push_back(std::move(deck.back())); // 一番最後のカードを移動
	deck.pop_back();                        // 移動後に元のデッキから削除
}

void CardManager::DeckShuffle() {
	// デッキシャッフル!!
	std::shuffle(deck.begin(), deck.end(), g);
	std::uniform_int_distribution<int> get_rand_uni_int(0, 1);
	for (int i = 0; i < deck.size(); i++) {
		deck[i]->SetIsReverse(static_cast<bool>(get_rand_uni_int(g)));
	}
}

void CardManager::DeckRefresh() {
	while (cemetery.size() > 0) {
		// cemetery から deck にカードを移動
		deck.push_back(std::move(cemetery.back())); // 一番最後のカードを移動
		cemetery.pop_back();                        // 移動後に元のデッキから削除
	}
	DeckShuffle();
}

void CardManager::AllHandLack() {
	handLack = 0;
	for (int i = 0; i < handCard.size(); i++) {
		handLack += handCard[i]->GetLuck();
	}
}
