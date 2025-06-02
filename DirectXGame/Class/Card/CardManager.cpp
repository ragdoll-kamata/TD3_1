#include "CardManager.h"
#include "EnemyManager.h"
#include <algorithm>
#include <iostream>

#include "Easings.h"
#include "Player.h"
#include "RelicEffectTiming.h"
#include "RelicManager.h"

#include "StandardAtack.h"
#include "StandardReverse.h"
#include "StandardRiskyAttack.h"
#include "StandardShield.h"

using namespace MathUtility;
void CardManager::Initialize(EnemyManager* enemy, Player* player) {
	enemyManager = enemy;
	player_ = player;

	std::random_device rd; // 乱数の種
	g.seed(rd());

	turnEndButton = std::make_unique<Button>();
	turnEndButton->Initialize(turnEndButtonStandbyPos, turnEndButtonSize, "UI/turnEndOn.png", {1.0f, 1.0f, 1.0f, 1.0f});
	turnEndButton->SetTextureRect({512.0f, 128.0f});
	turnEndNotButton = std::make_unique<Button>();
	turnEndNotButton->Initialize(turnEndButtonStandbyPos, turnEndButtonSize, "UI/turnEndOff.png", {1.0f, 1.0f, 1.0f, 1.0f});
	turnEndNotButton->SetTextureRect({512.0f, 128.0f});
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

	cardDrawSH = Audio::GetInstance()->LoadWave("SE/cardDraw.mp3");
	cardShuffleSH = Audio::GetInstance()->LoadWave("SE/cardShuffle.mp3");

	cardFactory_ = std::make_unique<CardFactory>();
}

void CardManager::BattleUpdata() {
	for (const auto& card : deck) {
		card->Updata();
	}
	for (const auto& card : handCard) {
		card->Updata();
	}
	CardDrawMove();
	CardLocationUpdate();
}

void CardManager::DrawBattle() {
	if (isReverseButton) {
		allReverseYssButton->Draw();
		allReverseNoButton->Draw();
	}
	if (handLack >= 0) {
		turnEndButton->Draw();
	} else {
		turnEndNotButton->Draw();
	}
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
	if (isDeck || isCemetery || isSelectionHand) {
		sprite.Draw();
	}
	if (isDeck) {
		for (int i = 0; i < deckDisplay.size(); i++) {
			deckDisplay[i]->Draw();
		}
		deckButton->Draw();
	} else if (isCemetery) {
		for (int i = 0; i < executionDisplay.size(); i++) {
			executionDisplay[i]->Draw();
		}
		cemeteryButton->Draw();
	} else if (isSelectionHand) {
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
		turnEndNotButton->SetPosition(Vector2Lerp(turnEndButtonStandbyPos, turnEndButtonPos, Easings::EaseOutQuart(t)));
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
		drawIndex += drawNum;
		CardDraw(drawNum);
	}
	if (cardDrawNum <= 0) {
		isReverseButton = true;
		if (CardConfirmation()) {
			Vector2 mousePos = Input::GetInstance()->GetMousePosition();
			if (Input::GetInstance()->IsTriggerMouse(0)) {
				if (allReverseYssButton->IsOnCollision(mousePos)) {
					is = true;
					for (int i = 0; i < handCard.size(); i++) {
						handCard[i]->SetIsReverse(!handCard[i]->GetIsReverse());
					}
					for (const auto& card : deck) {
						card->SetIsReverse(!card->GetIsReverse());
					}
				}

				if (allReverseNoButton->IsOnCollision(mousePos)) {
					is = true;
				}
				if (is) {
					isReverseButton = false;
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
								handCard[holdH]->SetTargetEnemy(enemyManager->GetEnemy(EH));           // ターゲットエネミーのセット
								executionCard = handCard[holdH].get();
								CardLocationMove(handCard[holdH], CardLocation::Execution); // ムーブ
								player_->GetStatus()->Effect(EffectTiming::OnExecution, StackDecreaseTiming::None);
							}
						} else {
							if (mousePos.y <= 360.0f) {
								executionCard = handCard[holdH].get();
								CardLocationMove(handCard[holdH], CardLocation::Execution); // ムーブ
								player_->GetStatus()->Effect(EffectTiming::OnExecution, StackDecreaseTiming::None);
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
		CardLocationMove(handCard.back(), CardLocation::Cemetery);
	}

	return true;
}

void CardManager::StartBattle() {
	number.SetNumber(0);
	// デッキ生成
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
		turnEndNotButton->SetPosition(Vector2Lerp(turnEndButtonPos, turnEndButtonStandbyPos, Easings::EaseOutQuart(t)));
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
	player_->GetStatus()->ClearShield();
	cardDrawNum = 0;
}

////////////////////////////////////////////////////////////////////////////////////////

void CardManager::DeckShuffle() {
	// デッキシャッフル!!
	std::shuffle(deck.begin(), deck.end(), g);
	std::uniform_int_distribution<int> get_rand_uni_int(0, 1);
	for (int i = 0; i < deck.size(); i++) {
		deck[i]->KSetIsReverse(static_cast<bool>(get_rand_uni_int(g)));
	}
	Audio::GetInstance()->PlayWave(cardShuffleSH);
}

void CardManager::DeckRefresh() {
	while (cemetery.size() > 0) {
		// cemetery から deck にカードを移動
		CardLocationMove(cemetery.back(), CardLocation::Deck); // ムーブ
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
			CardLocationMove(execution[0], CardLocation::Cemetery); // ムーブ
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
	float mouseWheel = 0.0f;
	if (Input::GetInstance()->GetWheel() != 0) {
		mouseWheel = static_cast<float>(Input::GetInstance()->GetWheel()) / 3.0f - prevWheel;
	}
	prevWheel = static_cast<float>(Input::GetInstance()->GetWheel()) / 3.0f;
	scroll += mouseWheel;
	if (Input::GetInstance()->IsTriggerMouse(0)) {
		if (deckButton->IsOnCollision(mousePos)) {
			if (!isDeck) {
				isDeck = true;
				deckDisplay.clear();
				for (const auto& card : deck) {
					deckDisplay.push_back(card.get());
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
			CardLocationMove(deck[i], deck[i]->GetCardLocation());
		}
	}
	for (int i = 0; i < handCard.size(); i++) {
		if (handCard[i]->GetCardLocation() != CardLocation::Hand) {
			CardLocationMove(handCard[i], handCard[i]->GetCardLocation());
		}
	}
	for (int i = 0; i < cemetery.size(); i++) {
		if (cemetery[i]->GetCardLocation() != CardLocation::Cemetery) {
			CardLocationMove(cemetery[i], cemetery[i]->GetCardLocation());
		}
	}
	for (int i = 0; i < execution.size(); i++) {
		if (execution[i]->GetCardLocation() != CardLocation::Execution) {
			CardLocationMove(execution[i], execution[i]->GetCardLocation());
		}
	}
}

void CardManager::CardLocationMove(std::unique_ptr<Card>& card, CardLocation cardLocation) {
	std::unique_ptr<Card> moveC = nullptr;
	switch (card->GetCardLocation()) {
	case CardLocation::Deck:
		for (auto it = deck.begin(); it != deck.end(); ++it) {
			if (it->get() == card.get()) {
				moveC = std::move(*it);
				deck.erase(it);
				break;
			}
		}
		break;
	case CardLocation::Hand:
		for (auto it = handCard.begin(); it != handCard.end(); ++it) {
			if (it->get() == card.get()) {
				moveC = std::move(*it);
				handCard.erase(it);
				break;
			}
		}
		break;
	case CardLocation::Cemetery:
		for (auto it = cemetery.begin(); it != cemetery.end(); ++it) {
			if (it->get() == card.get()) {
				moveC = std::move(*it);
				cemetery.erase(it);
				break;
			}
		}
		break;
	case CardLocation::Execution:
		for (auto it = execution.begin(); it != execution.end(); ++it) {
			if (it->get() == card.get()) {
				moveC = std::move(*it);
				execution.erase(it);
				break;
			}
		}
		break;
	}

	switch (cardLocation) {
	case CardLocation::Deck:
		moveC->SetCardLocation(CardLocation::Deck);
		deck.push_back(std::move(moveC)); // ムーブ
		break;
	case CardLocation::Hand:
		moveC->SetCardLocation(CardLocation::Hand);
		handCard.push_back(std::move(moveC)); // ムーブ
		break;
	case CardLocation::Cemetery:
		moveC->SetCardLocation(CardLocation::Cemetery);
		cemetery.push_back(std::move(moveC)); // ムーブ
		break;
	case CardLocation::Execution:
		moveC->SetCardLocation(CardLocation::Execution);
		execution.push_back(std::move(moveC)); // ムーブ
		break;
	}
}

void CardManager::CardDrawMove() {
	if (cardDrawTimer < kCardDrawTimer) {
		cardDrawTimer++;
	}
	if (cardShuffleTimer < kCardShuffleTimer) {
		cardShuffleTimer++;
	}
	if (cardDrawNum > 0) {

		if (cardShuffleTimer >= kCardShuffleTimer) {

			if (cardDrawTimer >= kCardDrawTimer) {
				if (deck.size() <= 0) {
					if (cemetery.size() <= 0) {
						return;
					}
					cardShuffleTimer = 0;
					DeckRefresh();
				} else {
					if (handCard.size() < 8) {
						Audio::GetInstance()->PlayWave(cardDrawSH, false, 0.5f);
						std::unique_ptr<Card>& card = deck.back(); // 一番最後のカードを参照
						if (cardDrawPositiveNum > 0) {
							card->SetIsReverse(false);
							cardDrawPositiveNum--;
						}
						if (cardDrawReverseNum > 0) {
							card->SetIsReverse(true);
							cardDrawReverseNum--;
						}
						card->SetSpritePos(deckButtonPos);
						CardLocationMove(card, CardLocation::Hand); // 手札に移動

						AllHandLack();
						cardDrawTimer = 0;
						cardDrawNum--;
					} else {
						cardDrawNum = 0;
					}
				}
			}
		}
	}
}

void CardManager::CardLocationMove(Card* card, CardLocation cardLocation) {
	std::unique_ptr<Card> moveC = nullptr;
	switch (card->GetCardLocation()) {
	case CardLocation::Deck:
		for (auto it = deck.begin(); it != deck.end(); ++it) {
			if (it->get() == card) {
				moveC = std::move(*it);
				deck.erase(it);
				break;
			}
		}
		break;
	case CardLocation::Hand:
		for (auto it = handCard.begin(); it != handCard.end(); ++it) {
			if (it->get() == card) {
				moveC = std::move(*it);
				handCard.erase(it);
				break;
			}
		}
		break;
	case CardLocation::Cemetery:
		for (auto it = cemetery.begin(); it != cemetery.end(); ++it) {
			if (it->get() == card) {
				moveC = std::move(*it);
				cemetery.erase(it);
				break;
			}
		}
		break;
	case CardLocation::Execution:
		for (auto it = execution.begin(); it != execution.end(); ++it) {
			if (it->get() == card) {
				moveC = std::move(*it);
				execution.erase(it);
				break;
			}
		}
		break;
	}
	switch (cardLocation) {
	case CardLocation::Deck:
		moveC->SetCardLocation(CardLocation::Deck);
		deck.push_back(std::move(moveC)); // ムーブ
		break;
	case CardLocation::Hand:
		moveC->SetCardLocation(CardLocation::Hand);
		handCard.push_back(std::move(moveC)); // ムーブ
		break;
	case CardLocation::Cemetery:
		moveC->SetCardLocation(CardLocation::Cemetery);
		cemetery.push_back(std::move(moveC)); // ムーブ
		break;
	case CardLocation::Execution:
		moveC->SetCardLocation(CardLocation::Execution);
		execution.push_back(std::move(moveC)); // ムーブ
		break;
	}
}

void CardManager::CardDraw(int num, int value, bool is) { 
	cardDrawNum += num;
	if (value > 0) {
		if (!is) {
			if (cardDrawReverseNum > 0) {
				cardDrawReverseNum -= value;
				if (cardDrawReverseNum < 0) {
					cardDrawPositiveNum -= cardDrawReverseNum;
					cardDrawReverseNum = 0;
				}
			} else {
				cardDrawPositiveNum += value;
			}
		} else {
			if (cardDrawPositiveNum > 0) {
				cardDrawPositiveNum -= value;
				if (cardDrawPositiveNum < 0) {
					cardDrawReverseNum -= cardDrawPositiveNum;
					cardDrawPositiveNum = 0;
				}
			} else {
				cardDrawReverseNum += value;
			}
		}
	}
	player_->GetStatus()->Effect(EffectTiming::OnDraw, StackDecreaseTiming::None);
}

int CardManager::RandomHandDeath(int num) {

	for (int i = 0; i < num; i++) {
		if (handCard.size() <= 0) {
			return num - i;
			break;
		}
		std::uniform_int_distribution<int> get_rand_uni_int(0, static_cast<int>(handCard.size()) - 1);
		int a = get_rand_uni_int(g);
		CardLocationMove(handCard[a], CardLocation::Cemetery); // 手札から墓地に移動
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
	sDeck.push_back(std::make_unique<StandardRiskyAttack>());

	sDeck.push_back(std::make_unique<StandardShield>());
	sDeck.push_back(std::make_unique<StandardShield>());
	sDeck.push_back(std::make_unique<StandardShield>());
	sDeck.push_back(std::make_unique<StandardShield>());
	sDeck.push_back(std::make_unique<StandardReverse>());

	for (int i = 0; i < sDeck.size(); i++) {
		sDeck[i]->Initialize();
		sDeck[i]->SetCardManager(this);
		sDeck[i]->SetBattleManager(battleManager_);
		sDeck[i]->SetPlayerStatus(player_->GetStatus());
	}
}

std::vector<std::unique_ptr<Card>> CardManager::RewardCardGeneration() {

	std::vector<std::unique_ptr<Card>> reward;
	std::unique_ptr<Card> card = CardLottery();
	cardFactory_->AddUnGenerationCard(card.get());
	reward.push_back(std::move(card));

	card = CardLottery();
	cardFactory_->AddUnGenerationCard(card.get());
	reward.push_back(std::move(card));

	card = CardLottery();
	cardFactory_->AddUnGenerationCard(card.get());
	reward.push_back(std::move(card));

	cardFactory_->ClearUnGenerationCard();

	for (int i = 0; i < reward.size(); i++) {
		reward[i]->Initialize();
		reward[i]->SetCardManager(this);
		reward[i]->SetBattleManager(battleManager_);
		reward[i]->SetPlayerStatus(player_->GetStatus());
		reward[i]->SetSpritePos({640.0f - (200.0f * ((reward.size() - 1) / 2.0f - i)), 360.0f});
		reward[i]->SetSize(1.2f);
		for (int j = 0; j < 5; j++) {
			reward[i]->Updata();
		}
	}

	return reward;
}

std::vector<Card*> CardManager::GetSDeck() {
	std::vector<Card*> display;
	for (int i = 0; i < sDeck.size(); i++) {
		display.push_back(sDeck[i].get());
	}
	// std::sort(display.begin(), display.end(), [](const Card* a, const Card* b) { return a->GetId() < b->GetId(); });
	for (int i = 0; i < display.size(); i++) {
		Vector2 pos = {640.0f - (160.0f * ((5 - 1) / 2.0f - (i % 5))), 380.0f - (175.0f * (((display.size() - 1) / 5) / 2.0f - (i / 5)))};
		display[i]->SetSpritePos(pos);
	}

	return display;
}

std::unique_ptr<Card> CardManager::CardLottery() {
	std::uniform_int_distribution<int> probability(1, 100);
	int i = probability(g);
	if (i <= kUncommonChanceValue) {
		return cardFactory_->UnCommonCardCreate(g);
	}
	i -= kUncommonChanceValue;
	if (i <= rareChanceValue) {
		rareChanceValue = kStartRareChanceValue;
		return cardFactory_->RareCardCreate(g);
	}
	i -= rareChanceValue;
	rareChanceValue += kUpRareChanceValue;
	return cardFactory_->CommonCardCreate(g);
}
