#include "RewardManager.h"
#include "CardReward.h"
#include "MapManager.h"
#include "TreasureReward.h"

void RewardManager::Initialize(CardManager* cardManager, RelicManager* relicManager) {
	cardManager_=cardManager;
	relicManager_ = relicManager;
	back.Initialize();
	back.SetSize({1280.0f, 720.0f});
	back.SetColor({0.0f, 0.0f, 0.0f, 0.9f});
	skip.Initialize({900.0f, 360.0f}, {200.0f, 50.0f}, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});
}

void RewardManager::Update() {
	if (isReward && isSelect) {
		Vector4 color = back.GetColor();
		back.SetColor({0.0f, 0.0f, 0.0f, MathUtility::Lerp(color.w, 0.7f, 0.3f)});
		is_ = false;
		for (int i = 0; i < rewards.size(); i++) {
			rewards[i]->SetIsU(false);
			is_ = rewards[i]->GetIsR();
			if (is_) {
				break;
			}
		}
		if (is_) {
			for (int i = 0; i < rewards.size(); i++) {
				rewards[i]->SetIsU(true);
			}
		}
		for (int i = 0; i < rewards.size(); i++) {
			rewards[i]->SetPos({640.0f, 300 + 41.0f * i});
			rewards[i]->Update();
		}
		std::erase_if(rewards, [](const auto& asd) { return asd->IsDelete(); });
		if (!is_) {
			if (Input::GetInstance()->IsTriggerMouse(0)) {
				if (skip.IsOnCollision(Input::GetInstance()->GetMousePosition())) {
					isSkip = true;
					if (isSkipForSelect) {
						isSelect = false;
					}
				}
			}
		}
	} else {
		back.SetColor({0.0f, 0.0f, 0.0f, 0.0f});
	}

}

void RewardManager::Draw() {
	if (IsReward() && isSelect) {
		back.Draw();
		skip.Draw();
		for (int i = 0; i < rewards.size(); i++) {
			rewards[i]->Draw();
		}
		if (is_) {
			back.Draw();
		}
		for (int i = 0; i < rewards.size(); i++) {
			rewards[i]->CardDraw();
		}
	}
}

void RewardManager::CreateBattleReward(BattleEnemyType battleEnemyType) {
	fCreateReward[battleEnemyType]();
	for (int i = 0; i < rewards.size(); i++) {
		rewards[i]->Initialize(cardManager_, relicManager_);
	}

	isReward = true;
	isSkip = false;
	isSkipForSelect = false;
	isSelect = true;
}

void RewardManager::CreateTreasureReward() {
	rewards.push_back(std::make_unique<TreasureReward>());
	for (int i = 0; i < rewards.size(); i++) {
		rewards[i]->Initialize(cardManager_, relicManager_);
	}
	isSkipForSelect = true;
	isReward = true;
	isSkip = false;
	isSelect = true;
}

void RewardManager::ClearReward() {
	rewards.clear();
	isReward = false;
	isSkip = false;
	isSelect = true;
}

void RewardManager::CreateBattleNormalReward() {
	rewards.push_back(std::make_unique<CardReward>());
}

void RewardManager::CreateBattleEliteReward() {
	rewards.push_back(std::make_unique<CardReward>());
	rewards.push_back(std::make_unique<TreasureReward>());
}

void RewardManager::CreateBattleBossReward() { isClear_ = true; }
