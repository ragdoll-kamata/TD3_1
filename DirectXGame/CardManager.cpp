#include "CardManager.h"
#include "CollisionDetection.h"
#include <algorithm>
#include "EnemyManager.h"
using namespace CollisionDetection;
using namespace MathUtility;
void CardManager::Initialize(EnemyManager* enemy) {
	enemyManager = enemy;
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


	turnEndButton = std::make_unique<Button>();
	turnEndButton->Initialize(turnEndButtonPos, turnEndButtonSize, "white1x1.png", {1.0f, 0.0f, 0.0f, 1.0f});


	allReverseYssButton = std::make_unique<Button>();
	allReverseYssButton->Initialize(allReverseYssButtonPos, allReverseButtonSize, "white1x1.png", {0.0f, 1.0f, 0.0f, 1.0f});

	allReverseNoButton = std::make_unique<Button>();
	allReverseNoButton->Initialize(allReverseNoButtonPos, allReverseButtonSize, "white1x1.png", {1.0f, 0.0f, 0.0f, 1.0f});

	number.Initialize({100.0f,500.0f});
}

void CardManager::BattleUpdata() { 
	mBattlePhase[battlePhase]();
}

void CardManager::DrawBattle() {
	if (isReverseButton) {
		allReverseYssButton->Draw();
		allReverseNoButton->Draw();
	}


	turnEndButton->Draw();
	number.Draw();
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
			if (allReverseYssButton->IsOnCollision(mousePos)) {
				isReverseButton = false;
				battlePhase = BattlePhase::MainTurn;
				drawIndex = 0;
				for (int i = 0; i < handCard.size(); i++) {
					handCard[i]->SetIsReverse(!handCard[i]->GetIsReverse());
				}
			}

			if (allReverseNoButton->IsOnCollision(mousePos)) {
				isReverseButton = false;
				battlePhase = BattlePhase::MainTurn;
				drawIndex = 0;
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

		if (handCard[i]->IsOnCollision(mousePos)) {
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
					if (handCard[i]->GetCardRange() == CardRange::One) {
						uint32_t EH = enemyManager->IsOnCollision(mousePos);

						if (EH > 0) {
							handCard[holdH]->SetTargetEnemy(enemyManager->GetEnemy(EH)); // ターゲットエネミーのセット
							execution.push_back(std::move(handCard[holdH]));             // ムーブ
							handCard.erase(handCard.begin() + holdH);                    // 元のリストから削除
						}
					} else {
						if (mousePos.y <= 360.0f) {
							execution.push_back(std::move(handCard[holdH])); // ムーブ
							handCard.erase(handCard.begin() + holdH);        // 元のリストから削除
						}
					}

					isHold = false;
				}
			}
		}
	}

	if (execution.size()) {
		EffectProcessing();
	}

	if (Input::GetInstance()->IsTriggerMouse(0)) {
		if (handLack >= 0) {
			if (turnEndButton->IsOnCollision(mousePos)) {
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
	AllHandLack();
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

void CardManager::EffectProcessing() {
	cemetery.push_back(std::move(execution[0])); // ムーブ
	execution.erase(execution.begin());          // 元のリストから削除
}

void CardManager::AllHandLack() {
	handLack = 0;
	for (int i = 0; i < handCard.size(); i++) {
		handLack += handCard[i]->GetLuck();
	}
	number.SetNumber(handLack);
}
