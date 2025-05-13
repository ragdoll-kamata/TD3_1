#include "CardFactory.h"

#include "AmplifierShield.h"
#include "Blow.h"
#include "DrawCard.h"
#include "PoisonDagger.h"
#include "Reverse.h"

#include "Bloodsucking.h"
#include "StrengthUp.h"
#include "VeryCareful.h"
#include "ClusterGrenade.h"

#include "AllReverse.h"
#include "MiniHeal.h"

#include <list>

std::unique_ptr<Card> CardFactory::CommonCardCreate(std::mt19937& random) {
	std::list<std::unique_ptr<Card>> commonCards;
	commonCards.push_back(std::make_unique<AmplifierShield>());
	commonCards.push_back(std::make_unique<Blow>());
	commonCards.push_back(std::make_unique<DrawCard>());
	commonCards.push_back(std::make_unique<PoisonDagger>());
	commonCards.push_back(std::make_unique<Reverse>());
	int i = 0;
	for (auto card : unGenerationCard) {
		RemoveSameClassCard(commonCards, card);
	}
	for (auto& card : commonCards) {
		card;
		i++;
	}
	std::uniform_int_distribution<int> dist(0, i - 1);
	int randomIndex = dist(random);
	auto it = std::next(commonCards.begin(), randomIndex);

	return std::move(*it);
}

std::unique_ptr<Card> CardFactory::UnCommonCardCreate(std::mt19937& random) { 
	std::list<std::unique_ptr<Card>> uncommonCards;
	uncommonCards.push_back(std::make_unique<Bloodsucking>());
	uncommonCards.push_back(std::make_unique<StrengthUp>());
	uncommonCards.push_back(std::make_unique<VeryCareful>());
	uncommonCards.push_back(std::make_unique<ClusterGrenade>());
	int i = 0;
	for (auto card : unGenerationCard) {
		RemoveSameClassCard(uncommonCards, card);
	}
	for (auto& card : uncommonCards) {
		card;
		i++;
	}
	std::uniform_int_distribution<int> dist(0, i - 1);
	int randomIndex = dist(random);
	auto it = std::next(uncommonCards.begin(), randomIndex);
	return std::move(*it);
}

std::unique_ptr<Card> CardFactory::RareCardCreate(std::mt19937& random) { 
	std::list<std::unique_ptr<Card>> rareCards;
	rareCards.push_back(std::make_unique<AllReverse>());
	rareCards.push_back(std::make_unique<MiniHeal>());
	int i = 0;
	for (auto card : unGenerationCard) {
		RemoveSameClassCard(rareCards, card);
	}
	for (auto& card : rareCards) {
		card;
		i++;
	}
	std::uniform_int_distribution<int> dist(0, i - 1);
	int randomIndex = dist(random);
	auto it = std::next(rareCards.begin(), randomIndex);
	return std::move(*it);
}

void CardFactory::RemoveSameClassCard(std::list<std::unique_ptr<Card>>& cardList, const Card* target) {
	for (auto it = cardList.begin(); it != cardList.end(); ++it) {
		if (typeid(**it) == typeid(*target)) {
			cardList.erase(it);
			break; // 一つだけ削除するなら break。すべて削除したい場合は break を外す
		}
	}
}