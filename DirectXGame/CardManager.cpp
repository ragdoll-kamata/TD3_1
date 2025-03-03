#include "CardManager.h"
#include <algorithm>
#include <iostream>
#include "EnemyManager.h"
#include "StandardAtack.h"
#include "StandardShield.h"
#include "Reverse.h"
#include "DrawCard.h"
using namespace MathUtility;
void CardManager::Initialize(EnemyManager* enemy, Player* player) {
	enemyManager = enemy;
	player_ = player;

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
	sDeck.push_back(std::make_unique<DrawCard>());
	sDeck.push_back(std::make_unique<DrawCard>());
	sDeck.push_back(std::make_unique<Reverse>());


	for (int i = 0; i < sDeck.size(); i++) {
		sDeck[i]->Initialize();
		sDeck[i]->SetCardManager(this);
		sDeck[i]->SetPlayer(player_);
	}

	StartBattle();


	turnEndButton = std::make_unique<Button>();
	turnEndButton->Initialize(turnEndButtonPos, turnEndButtonSize, "white1x1.png", {1.0f, 0.0f, 0.0f, 1.0f});


	allReverseYssButton = std::make_unique<Button>();
	allReverseYssButton->Initialize(allReverseYssButtonPos, allReverseButtonSize, "white1x1.png", {0.0f, 1.0f, 0.0f, 1.0f});

	allReverseNoButton = std::make_unique<Button>();
	allReverseNoButton->Initialize(allReverseNoButtonPos, allReverseButtonSize, "white1x1.png", {1.0f, 0.0f, 0.0f, 1.0f});

	deckButton = std::make_unique<Button>();
	deckButton->Initialize(deckButtonPos, deckButtonSize, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});

	cemeteryButton = std::make_unique<Button>();
	cemeteryButton->Initialize(cemeteryButtonPos, cemeteryButtonSize, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});

	selectHandButton = std::make_unique<Button>();
	selectHandButton->Initialize(selectHandButtonPos, selectHandButtonSize, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});

	number.Initialize({100.0f,500.0f});
	
	TH = TextureManager::GetInstance()->Load("white1x1.png");

	sprite.Initialize();
	sprite.SetTextureHandle(TH);
	sprite.SetSize({1280.0f, 720.0f});
	sprite.SetColor({0.0f, 0.0f, 0.0f, 0.5f});
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
	if (!isDeck) {
		deckButton->Draw();
	}
	if (!isCemetery) {
		cemeteryButton->Draw();
	}
	if (!isSelectionHand) {
		for (int i = 0; i < handCard.size(); i++) {
			handCard[i]->Draw();
		}
	}
	if (isDeck) {
		sprite.Draw();
		for (int i = 0; i < deckDisplay.size(); i++) {
			deckDisplay[i]->Draw();
		}
	}
	if (isDeck) {
		deckButton->Draw();
	}

	if (isCemetery) {
		sprite.Draw();
		for (int i = 0; i < executionDisplay.size(); i++) {
			executionDisplay[i]->Draw();
		}
	}
	if (isCemetery) {
		cemeteryButton->Draw();
	}
	if (isSelectionHand) {
		sprite.Draw();
		for (int i = 0; i < handCard.size(); i++) {
			handCard[i]->Draw();
		}
		if (isSelectOK) {
			selectHandButton->Draw();
		}
	}
}

void CardManager::StartMainTurn() {
	if (drawIndex < 5) {
		drawTimer++;

		if (drawTimer >= kDrawTimer) {
			drawTimer = 0;
			drawIndex++;
			CardDraw(1);
		}
	} else {
		isReverseButton = true;
		if (CardConfirmation()) {
			Vector2 mousePos = Input::GetInstance()->GetMousePosition();
			if (Input::GetInstance()->IsTriggerMouse(0)) {
				if (allReverseYssButton->IsOnCollision(mousePos)) {
					isReverseButton = false;
					battlePhase = BattlePhase::MainTurn;
					drawIndex = 0;
					for (int i = 0; i < handCard.size(); i++) {
						handCard[i]->SetIsReverse(!handCard[i]->GetIsReverse());
					}
					for (const auto& card : deck) {
						card->SetIsReverse(!card->GetIsReverse());
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

}

void CardManager::MainTurn() {
	Vector2 mousePos = Input::GetInstance()->GetMousePosition();
	AllHandLack();

	if (!isSelectionHand) {
		if (CardConfirmation()) {
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
			if (Input::GetInstance()->IsTriggerMouse(0)) {
				if (handLack >= 0) {
					if (turnEndButton->IsOnCollision(mousePos)) {
						battlePhase = BattlePhase::EndMainTurn;
					}
				}
			}
		}
	}
	if (execution.size()) {
		EffectProcessing();
	}
}

void CardManager::EndMainTurn() {
	while (handCard.size() > 0) {
		// handCard から cemetery にカードを移動
		cemetery.push_back(std::move(handCard.back())); // 一番最後のカードを移動
		handCard.pop_back();                            // 移動後に元のデッキから削除
	}
	enemyManager->SetIsEnemyTurn(true);
	battlePhase = BattlePhase::EnemyTurn;
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

void CardManager::EnemyTurn() {
	if (!enemyManager->GetIsEnemyTurn()) {
		battlePhase = BattlePhase::StartMainTurn;
	}

}

void CardManager::CardDraw(int num) {
	for (int j = 0; j < num; j++) {
		if (deck.size() <= 0) {
			DeckRefresh();
		}
		// deck から handCard にカードを移動
		handCard.push_back(std::move(deck.back())); // 一番最後のカードを移動
		deck.pop_back();                            // 移動後に元のデッキから削除
		for (int i = 0; i < handCard.size(); i++) {
			Vector2 pos = {640.0f - (121.0f * ((handCard.size() - 1) / 2.0f - i)), 600.0f};
			handCard[i]->SetSpritePos(pos);
		}
		AllHandLack();
	}
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
	bool is = false;
	if (!execution[0]->GetIsReverse()) {
		is = execution[0]->Effect();
	} else {
		is = execution[0]->ReverseEffect();
	}

	if (is) {
		cemetery.push_back(std::move(execution[0])); // ムーブ
		execution.erase(execution.begin());          // 元のリストから削除
	}
}

void CardManager::AllHandLack() {
	handLack = 0;
	for (int i = 0; i < handCard.size(); i++) {
		handLack += handCard[i]->GetLuck();
	}
	number.SetNumber(handLack);
}

bool CardManager::CardConfirmation() {
	Vector2 mousePos = Input::GetInstance()->GetMousePosition();
	if (Input::GetInstance()->IsTriggerMouse(0)) {
		if (deckButton->IsOnCollision(mousePos)) {
			if (!isDeck) {
				isDeck = true;
				deckDisplay.clear();
				for (int i = 0; i < deck.size(); i++) {

					deckDisplay.push_back(deck[i].get());
				}
				std::sort(deckDisplay.begin(), deckDisplay.end(), [](const Card* a, const Card* b) { return a->GetId() < b->GetId(); });
				for (int i = 0; i < deckDisplay.size(); i++) {
					Vector2 pos = {640.0f - (160.0f * ((5 - 1) / 2.0f - (i % 5))), 175.0f * (i / 5) + 90.0f};
					deckDisplay[i]->SetSpritePos(pos);
				}
			} else {
				isDeck = false;
			}
		}

		if (cemeteryButton->IsOnCollision(mousePos)) {
			if (!isCemetery) {
				isCemetery = true;
				executionDisplay.clear();
				for (int i = 0; i < cemetery.size(); i++) {

					executionDisplay.push_back(cemetery[i].get());
				}
				std::sort(executionDisplay.begin(), executionDisplay.end(), [](const Card* a, const Card* b) { return a->GetId() < b->GetId(); });
				for (int i = 0; i < executionDisplay.size(); i++) {
					Vector2 pos = {640.0f - (160.0f * ((5 - 1) / 2.0f - (i % 5))), 175.0f * (i / 5) + 90.0f};
					executionDisplay[i]->SetSpritePos(pos);
				}
			} else {
				isCemetery = false;
			}
		}
	}
	return !isDeck && !isCemetery;
}

void CardManager::RandomHandDeath(int num) {

	for (int i = 0; i < num; i++) {
		if (handCard.size() <= 0) {
			break;
		}
		std::uniform_int_distribution<int> get_rand_uni_int(0, static_cast<int>(handCard.size()) - 1);
		int a = get_rand_uni_int(g);
		cemetery.push_back(std::move(handCard[a])); // ムーブ
		handCard.erase(handCard.begin() + a);       // 元のリストから削除
	}




}

std::vector<Card*> CardManager::SelectionHand(int num) {
	Vector2 mousePos = Input::GetInstance()->GetMousePosition();
	
	isSelectionHand = true;
	for (int i = 0; i < handCard.size(); i++) {
		Vector2 pos = {640.0f - (121.0f * ((handCard.size() - 1) / 2.0f - i)), 600.0f};

		for (int j = 0; j < nnnum.size(); j++) {
			if (nnnum[j] == i) {
				pos.y -= 60.0f;
			}
		}

		handCard[i]->SetSpritePos(pos);

		if (handCard[i]->IsOnCollision(mousePos)) {
			if (Input::GetInstance()->IsTriggerMouse(0)) {
				bool is = false;
				for (int j = 0; j < nnnum.size(); j++) {
					if (nnnum[j] == i) {
						nnnum.erase(nnnum.begin() + j);
						is = true;
						break;
					}
				}
				if (!is) {
					if (num > nnnum.size()) {
						nnnum.push_back(i);
					}
				}
			}
		}
	}
	if (num <= nnnum.size()) {
		isSelectOK = true;
		if (selectHandButton->IsOnCollision(mousePos)) {
			if (Input::GetInstance()->IsTriggerMouse(0)) {
				std::vector<Card*> cards;
				for (int j = 0; j < nnnum.size(); j++) {
					cards.push_back(handCard[nnnum[j]].get());
				}
				isSelectionHand = false;
				isSelectOK = false;
				nnnum.clear();
				return cards;
			}
		}
	}
	return std::vector<Card*>();
}

