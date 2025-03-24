#include "CardFactory.h"

std::unique_ptr<Card> CardFactory::CommonCardCreate() { return std::unique_ptr<Card>(); }

std::unique_ptr<Card> CardFactory::UnCommonCardCreate() { return std::unique_ptr<Card>(); }

std::unique_ptr<Card> CardFactory::RareCardCreate() { return std::unique_ptr<Card>(); }
