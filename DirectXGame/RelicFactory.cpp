#include "RelicFactory.h"
#include <random>

#include "SakeCup.h"
#include "BlankRelic.h"

std::unique_ptr<Relic> RelicFactory::CreateRandomRelic(int& unCommon, int& rare) {
	// 乱数生成器の初期化
	std::random_device rd; // 乱数の種
	std::mt19937 g(rd());  // メルセンヌ・ツイスタ（高品質な乱数生成）
	std::uniform_int_distribution<int> get_rand_uni_int(0, 100); // 0から100までの一様分布
	int rand = get_rand_uni_int(g);
	if (rand < rare) {
		rare = 0;
		return CreateRareRelic();
	}
	rand -= rare;
	if (rand < unCommon) {
		unCommon = 0;
		return CreateUnCommonRelic();
	}

	isRare = false;
	return CreateCommonRelic();
}

std::unique_ptr<Relic> RelicFactory::CreateCommonRelic() { return std::unique_ptr<Relic>(); }

std::unique_ptr<Relic> RelicFactory::CreateUnCommonRelic() { return std::unique_ptr<Relic>(); }

std::unique_ptr<Relic> RelicFactory::CreateRareRelic() { 
	if (!electedRelic.contains("SakeCup")) {
		electedRelic.insert({"SakeCup", ""});
		return std::make_unique<SakeCup>();
	}


	return CreateUnCommonRelic();
}

std::unique_ptr<Relic> RelicFactory::ReCreateRandomRelic() {
	if (isCommon) {
		return CreateCommonRelic();
	}
	if (isUnCommon) {
		return CreateUnCommonRelic();
	}
	if (isRare) {
		return CreateRareRelic();
	}
	return std::unique_ptr<BlankRelic>();
}
