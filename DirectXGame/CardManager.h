#pragma once
#include <memory>
#include <vector>
#include "Card.h"
#include <random>
class CardManager {
public:

	void Initialize();
	void Updata();

	void DeckShuffle();

	void AllHandLack();

	void StartBattle();

	void EndBattle();


private:
	// シャッフルのための乱数エンジンを用意
	std::random_device rd; // 乱数の種
	std::mt19937 g;  // メルセンヌ・ツイスタ（高品質な乱数生成）

	std::vector<std::unique_ptr<Card>> sDeck;
	std::vector<std::unique_ptr<Card>> deck;
	std::vector<std::unique_ptr<Card>> cemetery;
	std::vector<std::unique_ptr<Card>> handCard;
	std::vector<std::unique_ptr<Card>> execution;
	int handLack;
};
