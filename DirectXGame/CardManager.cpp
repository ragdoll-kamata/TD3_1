#include "CardManager.h"
#include "CollisionDetection.h"
#include <algorithm>
using namespace CollisionDetection;
using namespace MathUtility;
void CardManager::Initialize() {
	std::random_device rd; // 乱数の種
	g.seed(rd());

	deck.push_back(std::make_unique<StandardAtack>());
	deck.push_back(std::make_unique<StandardAtack>());
	deck.push_back(std::make_unique<StandardAtack>());
	deck.push_back(std::make_unique<StandardAtack>());
	deck.push_back(std::make_unique<StandardAtack>());
	deck.push_back(std::make_unique<StandardAtack>());
	deck.push_back(std::make_unique<StandardAtack>());
	deck.push_back(std::make_unique<StandardAtack>());
	deck.push_back(std::make_unique<StandardAtack>());
	deck.push_back(std::make_unique<StandardAtack>());


	for (int i = 0; i < deck.size(); i++) {
		deck[i]->Initialize();
	}
}

void CardManager::BattleUpdata() { 
	mBattlePhase[battlePhase]();
}

void CardManager::DrawBattle() {
	for (int i = 0; i < handCard.size(); i++) {
		handCard[i]->Draw();
	}
}

void CardManager::StartMainTurn() {
	drawTimer++;

	if (drawTimer >= kDrawTimer){
		drawTimer = 0;
		drawIndex++;
		CardDraw();
		for (int i = 0; i < handCard.size(); i++) {
			Vector2 pos = {640.0f - (121.0f * ((handCard.size() - 1) / 2.0f - i)), 600.0f};
			handCard[i]->SetSpritePos(pos);
		}
	}

	if (drawIndex >= 5) {
		battlePhase = BattlePhase::MainTurn;
	}

}

void CardManager::MainTurn() {
	Vector2 mousePos = Input::GetInstance()->GetMousePosition();

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
					isHold = false;
				}
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
}

void CardManager::StartBattle() {
	//デッキ生成
	for (const auto& card : sDeck) {
		deck.push_back(card->clone()); // クローンを作る
	}
	// デッキシャッフル!!
	std::shuffle(deck.begin(), deck.end(), g);
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

void CardManager::DeckRefresh() {

	// cemetery から deck にカードを移動
	deck.push_back(std::move(cemetery.back())); // 一番最後のカードを移動
	cemetery.pop_back();                        // 移動後に元のデッキから削除

	// デッキシャッフル!!
	std::shuffle(deck.begin(), deck.end(), g);
}

void CardManager::AllHandLack() {
	for (int i = 0; i < handCard.size(); i++) {
		handLack += handCard[i]->GetLuck();
	}
}
