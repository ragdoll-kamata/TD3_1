#include "CardManager.h"
#include <algorithm>
#include <iostream>
#include "EnemyManager.h"


#include "Player.h"
#include "Easings.h"
#include "RelicManager.h"
#include "RelicEffectTiming.h"

#include "StandardAtack.h"
#include "StandardShield.h"
#include "Reverse.h"
#include "DrawCard.h"
#include "PoisonDagger.h"
#include "Blow.h"
#include "StrengthUp.h"
#include "AllReverse.h"
#include "Bloodsucking.h"
#include "VeryCareful.h"
#include "MiniHeal.h"

using namespace MathUtility;
void CardManager::Initialize(EnemyManager* enemy, Player* player) {
	enemyManager = enemy;
	player_ = player;

	std::random_device rd; // 乱数の種
	g.seed(rd());

	turnEndButton = std::make_unique<Button>();
	turnEndButton->Initialize(turnEndButtonStandbyPos, turnEndButtonSize, "white1x1.png", {1.0f, 0.0f, 0.0f, 1.0f});


	allReverseYssButton = std::make_unique<Button>();
	allReverseYssButton->Initialize(allReverseYssButtonPos, allReverseButtonSize, "white1x1.png", {0.0f, 1.0f, 0.0f, 1.0f});

	allReverseNoButton = std::make_unique<Button>();
	allReverseNoButton->Initialize(allReverseNoButtonPos, allReverseButtonSize, "white1x1.png", {1.0f, 0.0f, 0.0f, 1.0f});

	deckButton = std::make_unique<Button>();
	deckButton->Initialize(deckButtonStandbyPos, deckButtonSize, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});

	cemeteryButton = std::make_unique<Button>();
	cemeteryButton->Initialize(cemeteryButtonStandbyPos, cemeteryButtonSize, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});

	selectHandButton = std::make_unique<Button>();
	selectHandButton->Initialize(selectHandButtonPos, selectHandButtonSize, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});

	number.Initialize(numberStandbyPos);
	number.SetNumber(0);
	
	TH = TextureManager::GetInstance()->Load("white1x1.png");

	sprite.Initialize();
	sprite.SetTextureHandle(TH);
	sprite.SetSize({1280.0f, 720.0f});
	sprite.SetColor({0.0f, 0.0f, 0.0f, 0.5f});
}

void CardManager::BattleUpdata() {
	for (const auto& card : deck) {
		card->Updata();
	}
	for (const auto& card : handCard) {
		card->Updata();
	}
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
		deckButton->Draw();
	}

	if (isCemetery) {
		sprite.Draw();
		for (int i = 0; i < executionDisplay.size(); i++) {
			executionDisplay[i]->Draw();
		}
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


//////////////////////////////////////////////////////////////////////////////////////

bool CardManager::StartBattleTrue() {
	if (startTimer <= kStartTimer) {
		float t = static_cast<float>(startTimer) / static_cast<float>(kStartTimer);
		turnEndButton->SetPosition(Vector2Lerp(turnEndButtonStandbyPos, turnEndButtonPos, Easings::EaseOutQuart(t)));
		deckButton->SetPosition(Vector2Lerp(deckButtonStandbyPos, deckButtonPos, Easings::EaseOutQuart(t)));
		cemeteryButton->SetPosition(Vector2Lerp(cemeteryButtonStandbyPos, cemeteryButtonPos, Easings::EaseOutQuart(t)));
		number.SetPosition(Vector2Lerp(numberStandbyPos, numberPos, Easings::EaseOutQuart(t)));

		startTimer++;
		return false;
	}

	drawNum = 5;
	startTimer = 0;
	relicManager_->RelicEffect(RelicEffectTiming::StartOfBattle);
	return true;
}

bool CardManager::StartMainTurn() {
	if (!isStartRelic) {
		relicManager_->RelicEffect(RelicEffectTiming::StartOfTurn);
		isStartRelic = true;
	}
	bool is = false;
	if (drawIndex < drawNum) {
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
					is = true;
					drawNum = 5;
					drawIndex = 0;
					for (int i = 0; i < handCard.size(); i++) {
						handCard[i]->SetIsReverse(!handCard[i]->GetIsReverse());
					}
					for (const auto& card : deck) {
						card->SetIsReverse(!card->GetIsReverse());
					}
					isStartRelic = false;
				}

				if (allReverseNoButton->IsOnCollision(mousePos)) {
					isReverseButton = false;
					is = true;
					drawIndex = 0;
					drawNum = 5;
					isStartRelic = false;
				}
			}
		}
	}
	for (int i = 0; i < handCard.size(); i++) {
		HandCardSetSpritePos(i, {640.0f - (122.0f * ((handCard.size() - 1) / 2.0f - i)), 600.0f});
	}
	return is;
}

bool CardManager::MainTurn() {
	bool is = false;
	Vector2 mousePos = Input::GetInstance()->GetMousePosition();
	AllHandLack();

	if (!isSelectionHand) {
		if (CardConfirmation()) {
			for (int i = 0; i < handCard.size(); i++) {
				HandCardSetSpritePos(i, {640.0f - (122.0f * ((handCard.size() - 1) / 2.0f - i)), 600.0f});

				if (handCard[i]->IsOnCollision(mousePos)) {
					if (Input::GetInstance()->IsTriggerMouse(0)) {
						holdH = i;
						isHold = true;
						handCard[i]->SetSpritePos(mousePos);
					}
				}
			}

			if (isHold) {
				if (Input::GetInstance()->IsPressMouse(0)) {
					handCard[holdH]->SetSpritePos(mousePos);
				} else {
					if (handCard[holdH]->GetIsPlay()) {
						if (handCard[holdH]->GetCardRange() == CardRange::One) {
							uint32_t EH = enemyManager->IsOnCollision(mousePos);

							if (EH > 0) {
								handCard[holdH]->SetTargetEnemy(enemyManager->GetEnemy(EH)); // ターゲットエネミーのセット
								CardLocationMove(std::move(handCard[holdH]), CardLocation::Execution); // ムーブ
								handCard.erase(handCard.begin() + holdH);                    // 元のリストから削除
							}
						} else {
							if (mousePos.y <= 360.0f) {
								CardLocationMove(std::move(handCard[holdH]), CardLocation::Execution); // ムーブ
								handCard.erase(handCard.begin() + holdH);        // 元のリストから削除
							}
						}
					}

					isHold = false;
				}
			}

			if (Input::GetInstance()->IsTriggerMouse(0)) {
				if (handLack >= 0) {
					if (turnEndButton->IsOnCollision(mousePos)) {
						is = true;
					}
				}
			}

		}
	}

	if (execution.size()) {
		EffectProcessing();
	}
	CardLocationUpdate();
	return is;
}

bool CardManager::EndMainTurn() {
	while (handCard.size() > 0) {
		// handCard から cemetery にカードを移動
		CardLocationMove(std::move(handCard.back()), CardLocation::Cemetery);
		handCard.pop_back();                            // 移動後に元のデッキから削除
	}

	return true;
}

void CardManager::StartBattle() {
	number.SetNumber(0);
	//デッキ生成
	for (const auto& card : sDeck) {
		deck.push_back(card->clone()); // クローンを作る
	}
	DeckShuffle();
}

bool CardManager::EndBattleTrue() {
	if (endTimer <= kEndTimer) {
		float t = static_cast<float>(endTimer) / static_cast<float>(kEndTimer);
		for (int i = 0; i < handCard.size(); i++) {
			Vector2 pos = {640.0f - (121.0f * ((handCard.size() - 1) / 2.0f - i)), 600.0f};

			Vector2 pos2 = {0.0f, Lerp(0.0f, 300.0f, Easings::EaseOutQuart(t))};
			HandCardSetSpritePos(i, pos + pos2, 0.3f);
		}
		turnEndButton->SetPosition(Vector2Lerp(turnEndButtonPos, turnEndButtonStandbyPos, Easings::EaseOutQuart(t)));
		deckButton->SetPosition(Vector2Lerp(deckButtonPos, deckButtonStandbyPos, Easings::EaseOutQuart(t)));
		cemeteryButton->SetPosition(Vector2Lerp(cemeteryButtonPos, cemeteryButtonStandbyPos, Easings::EaseOutQuart(t)));
		number.SetPosition(Vector2Lerp(numberPos, numberStandbyPos, Easings::EaseOutQuart(t)));

		endTimer++;
		return false;
	}
	EndBattle();
	endTimer = 0;
	return true;
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


////////////////////////////////////////////////////////////////////////////////////////

void CardManager::DeckShuffle() {
	// デッキシャッフル!!
	std::shuffle(deck.begin(), deck.end(), g);
	std::uniform_int_distribution<int> get_rand_uni_int(0, 1);
	for (int i = 0; i < deck.size(); i++) {
		deck[i]->KSetIsReverse(static_cast<bool>(get_rand_uni_int(g)));
	}
}

void CardManager::DeckRefresh() {
	while (cemetery.size() > 0) {
		// cemetery から deck にカードを移動
		CardLocationMove(std::move(cemetery.back()), CardLocation::Deck); // ムーブ
		cemetery.pop_back();                        // 移動後に元のデッキから削除
	}
	DeckShuffle();
}

void CardManager::EffectProcessing() {
	bool is = false;
	
	is = execution[0]->StartEffect();

	if (is) {
		executionCardType = execution[0]->GetCardType();
		if (execution[0]->GetCardType() == CardType::Ability) {
			execution.erase(execution.begin()); // 元のリストから削除
		} else {
			CardLocationMove(std::move(execution[0]), CardLocation::Cemetery); // ムーブ
			execution.erase(execution.begin());          // 元のリストから削除
		}
		relicManager_->RelicEffect(RelicEffectTiming::Play);
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
	float mouseWheel = static_cast<float>(Input::GetInstance()->GetWheel()) / 3.0f - prevWheel;
	prevWheel = static_cast<float>(Input::GetInstance()->GetWheel()) / 3.0f;
	scroll += mouseWheel;
	if (Input::GetInstance()->IsTriggerMouse(0)) {
		if (deckButton->IsOnCollision(mousePos)) {
			if (!isDeck) {
				isDeck = true;
				deckDisplay.clear();
				for (int i = 0; i < deck.size(); i++) {

					deckDisplay.push_back(deck[i].get());
				}
				std::sort(deckDisplay.begin(), deckDisplay.end(), [](const Card* a, const Card* b) { return a->GetId() < b->GetId(); });
				sPos.resize(deckDisplay.size());
				float a = static_cast<float>((deckDisplay.size() - 1) / 5);
				for (int i = 0; i < sPos.size(); i++) {
					sPos[i] = {640.0f - (160.0f * ((5 - 1) / 2.0f - (i % 5))), 380.0f + (175.0f * (a - (a - (i / 5)))) - 175.0f};
					deckDisplay[i]->SetSpritePos(sPos[i]);
					deckDisplay[i]->Updata();
				}
			} else {
				isDeck = false;
				scroll = 0;
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
				sPos.resize(executionDisplay.size());
				float a = static_cast<float>((executionDisplay.size() - 1) / 5);
				for (int i = 0; i < sPos.size(); i++) {
					sPos[i] = {640.0f - (160.0f * ((5 - 1) / 2.0f - (i % 5))), 380.0f + (175.0f * (a - (a - (i / 5)))) - 175.0f};
					executionDisplay[i]->SetSpritePos(sPos[i]);
					executionDisplay[i]->Updata();
				}
			} else {
				isCemetery = false;
				scroll = 0;
			}
		}
	}
	if (isDeck) {
		float a = static_cast<float>((deckDisplay.size() - 1) / 5);

		float sc = std::clamp<float>(scroll, std::min<float>(-175.0f * (a - 2), 0), 0);
		scroll = Lerp(scroll, sc, 0.4f);
		for (int i = 0; i < deckDisplay.size(); i++) {
			deckDisplay[i]->SetSpritePos(Vector2Lerp(deckDisplay[i]->GetSpritePos(), {sPos[i].x, sPos[i].y + scroll}, 0.1f));
			deckDisplay[i]->Updata();
		}
	}

	if (isCemetery) {
		float a = static_cast<float>((executionDisplay.size() - 1) / 5);

		float sc = std::clamp<float>(scroll, std::min<float>(-175.0f * (a - 2), 0), 0);
		scroll = Lerp(scroll, sc, 0.4f);
		for (int i = 0; i < executionDisplay.size(); i++) {
			executionDisplay[i]->SetSpritePos(Vector2Lerp(executionDisplay[i]->GetSpritePos(), {sPos[i].x, sPos[i].y + scroll}, 0.1f));
			executionDisplay[i]->Updata();
		}
	}
	return !isDeck && !isCemetery;
}

void CardManager::HandCardSetSpritePos(int i, Vector2 pos, float t) { handCard[i]->SetSpritePos(Vector2Lerp(handCard[i]->GetSpritePos(), pos, t)); }

void CardManager::CardLocationUpdate() {
	for (int i = 0; i < deck.size(); i++) {
		if (deck[i]->GetCardLocation() != CardLocation::Deck) {
			CardLocationMove(std::move(deck[i]), deck[i]->GetCardLocation());
			deck.erase(deck.begin() + i); // 元のデッキから削除
		}
	}
	for (int i = 0; i < handCard.size(); i++) {
		if (handCard[i]->GetCardLocation() != CardLocation::Hand) {
			CardLocationMove(std::move(handCard[i]), handCard[i]->GetCardLocation());
			handCard.erase(handCard.begin() + i); // 元のデッキから削除
		}
	}
	for (int i = 0; i < cemetery.size(); i++) {
		if (cemetery[i]->GetCardLocation() != CardLocation::Cemetery) {
			CardLocationMove(std::move(cemetery[i]), cemetery[i]->GetCardLocation());
			cemetery.erase(cemetery.begin() + i); // 元のデッキから削除
		}
	}
	for (int i = 0; i < execution.size(); i++) {
		if (execution[i]->GetCardLocation() != CardLocation::Execution) {
			CardLocationMove(std::move(execution[i]), execution[i]->GetCardLocation());
			execution.erase(execution.begin() + i); // 元のデッキから削除
		}
	}
}

void CardManager::CardLocationMove(std::unique_ptr<Card> card, CardLocation cardLocation) { 
	switch (cardLocation) {
	case CardLocation::Deck:
		card->SetCardLocation(CardLocation::Deck);
		deck.push_back(std::move(card)); // ムーブ
		break;
	case CardLocation::Hand:
		card->SetCardLocation(CardLocation::Hand);
		handCard.push_back(std::move(card)); // ムーブ
		break;
	case CardLocation::Cemetery:
		card->SetCardLocation(CardLocation::Cemetery);
		cemetery.push_back(std::move(card)); // ムーブ
		break;
	case CardLocation::Execution:
		card->SetCardLocation(CardLocation::Execution);
		execution.push_back(std::move(card)); // ムーブ
		break;
	}
}

void CardManager::CardDraw(int num) {
	for (int j = 0; j < num; j++) {
		if (deck.size() <= 0) {
			if (cemetery.size() <= 0) {
				return;
			}
			DeckRefresh();
		}

		std::unique_ptr<Card> card = std::move(deck.back()); // 一番最後のカードを移動
		deck.pop_back();                                     // 移動後に元のデッキから削除

		card->SetSpritePos(deckButtonPos);
		CardLocationMove(std::move(card), CardLocation::Hand); // 手札に移動

		AllHandLack();
	}
}

int CardManager::RandomHandDeath(int num) {

	for (int i = 0; i < num; i++) {
		if (handCard.size() <= 0) {
			return num - i;
			break;
		}
		std::uniform_int_distribution<int> get_rand_uni_int(0, static_cast<int>(handCard.size()) - 1);
		int a = get_rand_uni_int(g);
		CardLocationMove(std::move(handCard[a]), CardLocation::Cemetery); // 手札から墓地に移動
		handCard.erase(handCard.begin() + a);       // 元のリストから削除
	}
	return 0;
}

std::vector<Card*> CardManager::SelectionHand(int num, bool isMax) {
	Vector2 mousePos = Input::GetInstance()->GetMousePosition();

	isSelectOK = false;
	if (isMax) {
		if (handCard.size() <= num) {
			std::vector<Card*> cards;
			if (handCard.size() <= 0) {
				cards.push_back(nullptr);
			}
			for (int i = 0; i < handCard.size(); i++) {
				cards.push_back(handCard[i].get());
			}
			return cards;
		}
	}
	isSelectionHand = true;
	for (int i = 0; i < handCard.size(); i++) {
		Vector2 pos = {640.0f - (122.0f * ((handCard.size() - 1) / 2.0f - i)), 600.0f};

		for (int j = 0; j < nnnum.size(); j++) {
			if (nnnum[j] == i) {
				pos.y -= 60.0f;
			}
		}

		HandCardSetSpritePos(i, pos);

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
	if (num <= nnnum.size() || !isMax) {
		isSelectOK = true;
		if (selectHandButton->IsOnCollision(mousePos)) {
			if (Input::GetInstance()->IsTriggerMouse(0)) {
				std::vector<Card*> cards;
				for (int j = 0; j < nnnum.size(); j++) {
					cards.push_back(handCard[nnnum[j]].get());
				}
				if (cards.size() <= 0) {
					cards.push_back(nullptr);
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

void CardManager::StartCreateSDeck() {
	sDeck.push_back(std::make_unique<StandardAtack>());
	sDeck.push_back(std::make_unique<StandardAtack>());
	sDeck.push_back(std::make_unique<StandardAtack>());
	sDeck.push_back(std::make_unique<StandardAtack>());
	sDeck.push_back(std::make_unique<VeryCareful>());

	sDeck.push_back(std::make_unique<MiniHeal>());
	sDeck.push_back(std::make_unique<StandardShield>());
	sDeck.push_back(std::make_unique<StandardShield>());
	sDeck.push_back(std::make_unique<StandardShield>());
	sDeck.push_back(std::make_unique<StandardShield>());

	sDeck.push_back(std::make_unique<DrawCard>());
	sDeck.push_back(std::make_unique<DrawCard>());
	sDeck.push_back(std::make_unique<AllReverse>());
	sDeck.push_back(std::make_unique<StrengthUp>());
	sDeck.push_back(std::make_unique<Blow>());

	for (int i = 0; i < sDeck.size(); i++) {
		sDeck[i]->Initialize();
		sDeck[i]->SetCardManager(this);
		sDeck[i]->SetBattleManager(battleManager_);
		sDeck[i]->SetPlayerStatus(player_->GetStatus());
	}
}

std::vector<std::unique_ptr<Card>> CardManager::RewardCardGeneration() {

	std::vector<std::unique_ptr<Card>> reward;
	reward.push_back(std::make_unique<DrawCard>());
	reward.push_back(std::make_unique<Blow>());
	reward.push_back(std::make_unique<Reverse>());

	for (int i = 0; i < reward.size(); i++) {
		reward[i]->Initialize();
		reward[i]->SetCardManager(this);
		reward[i]->SetBattleManager(battleManager_);
		reward[i]->SetPlayerStatus(player_->GetStatus());
		reward[i]->SetSpritePos({640.0f - (200.0f * ((reward.size() - 1) / 2.0f - i)), 360.0f});
		reward[i]->SetSize(1.2f);
	}

	return reward;
}

std::vector<Card*> CardManager::GetSDeck() {
	std::vector<Card*> display;
	for (int i = 0; i < sDeck.size(); i++) {
		display.push_back(sDeck[i].get());
	}
	//std::sort(display.begin(), display.end(), [](const Card* a, const Card* b) { return a->GetId() < b->GetId(); });
	for (int i = 0; i < display.size(); i++) {
		Vector2 pos = {640.0f - (160.0f * ((5 - 1) / 2.0f - (i % 5))), 380.0f - (175.0f * (((display.size() - 1) / 5) / 2.0f - (i / 5)))};
		display[i]->SetSpritePos(pos);
	}

	return display;
}


