#pragma once
#include <memory>
#include <vector>
#include "StandardAtack.h"
#include "StandardShield.h"

#include <random>
#include <KamataEngine.h>
#include <unordered_map>
#include <functional>
#include "Button.h"
#include "numberSprite.h"

class EnemyManager;

using namespace KamataEngine;
class CardManager {
public:
	enum class BattlePhase {
		StartMainTurn,
		MainTurn,
		EndMainTurn,
		EnemyTurn,
	};


	void Initialize(EnemyManager* enemy);
	void BattleUpdata();



	void DrawBattle();



	void StartMainTurn();

	void MainTurn();

	void EndMainTurn();

	void StartBattle();

	void EndBattle();

	void EnemyTurn();

	void CardDraw();
	
	void DeckShuffle();

	void DeckRefresh();

	void EffectProcessing();

	void AllHandLack();


private:
	// シャッフルのための乱数エンジンを用意
	std::mt19937 g;  // メルセンヌ・ツイスタ（高品質な乱数生成）

	std::vector<std::unique_ptr<Card>> sDeck;
	std::vector<std::unique_ptr<Card>> deck;
	std::vector<std::unique_ptr<Card>> cemetery;
	std::vector<std::unique_ptr<Card>> handCard;
	std::vector<std::unique_ptr<Card>> execution;
	int handLack;

	int holdH;
	bool isHold;

	std::unordered_map<BattlePhase, std::function<void()>> mBattlePhase{
	    {BattlePhase::StartMainTurn, [this]() { StartMainTurn(); }},
	    {BattlePhase::MainTurn,      [this]() { MainTurn(); }     },
	    {BattlePhase::EndMainTurn,   [this]() { EndMainTurn(); }  },
	    {BattlePhase::EnemyTurn,     [this]() { EnemyTurn(); }    },
	};
	BattlePhase battlePhase = BattlePhase::StartMainTurn;

	int drawIndex = 0;
	int drawTimer = 0;
	const int kDrawTimer = 10;

	const Vector2 turnEndButtonPos = {1100.0f, 450.0f};
	const Vector2 turnEndButtonSize = {160.0f, 40.0f};

	const Vector2 allReverseButtonSize = {120.0f, 40.0f};
	const Vector2 allReverseYssButtonPos = {640.0f - allReverseButtonSize.x / 2.0f - 20.0f, 360.0f};
	const Vector2 allReverseNoButtonPos = {640.0f + allReverseButtonSize.x / 2.0f + 20.0f, 360.0f};

	std::unique_ptr<Button> turnEndButton;
	std::unique_ptr<Button> allReverseYssButton;
	std::unique_ptr<Button> allReverseNoButton;



	bool isReverseButton = false;

	EnemyManager* enemyManager = nullptr;

	NumberSprite number;
};
