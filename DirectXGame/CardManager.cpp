#include "CardManager.h"

void CardManager::Initialize() {
	g.seed(rd);
}

void CardManager::Updata() {}

void CardManager::DeckShuffle() {

	// cemetery から deck にカードを移動
	deck.push_back(std::move(cemetery.back())); // 一番最後のカードを移動
	cemetery.pop_back();                        // 移動後に元のデッキから削除

	//デッキシャッフル!!
	std::shuffle(deck.begin(), deck.end(), g);
}

void CardManager::AllHandLack() {
	for (int i = 0; i < handCard.size(); i++) {
		handLack += handCard[i]->GetLuck();
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
