#pragma once
#include <memory>
#include "Card.h"
#include <random>
class CardFactory {
public:
	std::unique_ptr<Card> CommonCardCreate(std::mt19937& random);
	std::unique_ptr<Card> UnCommonCardCreate(std::mt19937& random);
	std::unique_ptr<Card> RareCardCreate(std::mt19937& random);

	void AddUnGenerationCard(Card* card) { unGenerationCard.push_back(card); }
	void ClearUnGenerationCard() { unGenerationCard.clear(); }

private:
	void RemoveSameClassCard(std::list<std::unique_ptr<Card>>& cardList, const Card* target);
private:
	std::list<Card*> unGenerationCard;
};
