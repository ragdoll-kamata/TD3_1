#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "Relic.h"
class RelicFactory {
public:

	std::unique_ptr<Relic> CreateRandomRelic(int& unCommon, int& rare);

	std::unique_ptr<Relic> CreateCommonRelic();

	std::unique_ptr<Relic> CreateUnCommonRelic();

	std::unique_ptr<Relic> CreateRareRelic();

	std::unique_ptr<Relic> ReCreateRandomRelic();

private:
	std::unordered_map<std::string, std::string> electedRelic;
	bool isCommon = true;
	bool isUnCommon = true;
	bool isRare = true;
};
