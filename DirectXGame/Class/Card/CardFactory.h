#pragma once
#include <memory>
#include "Card.h"
class CardFactory {
public:
	std::unique_ptr<Card> CommonCardCreate();
	std::unique_ptr<Card> UnCommonCardCreate();
	std::unique_ptr<Card> RareCardCreate();
};
