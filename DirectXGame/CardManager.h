#pragma once
#include <memory>
#include <vector>
#include "Card.h"

#include <random>
#include <KamataEngine.h>
#include <unordered_map>
#include <functional>
#include "Button.h"
#include "numberSprite.h"

class EnemyManager;
class Player;

using namespace KamataEngine;
class CardManager {
public:
	enum class BattlePhase {
		StartMainTurn,
		MainTurn,
		EndMainTurn,
		EnemyTurn,
	};


	void Initialize(EnemyManager* enemy, Player* player);
	void BattleUpdata();



	void DrawBattle();



	void StartMainTurn();

	void MainTurn();

	void EndMainTurn();

	void StartBattle();

	void EndBattle();

	void EnemyTurn();

	void CardDraw(int num);
	
	void DeckShuffle();

	void DeckRefresh();

	void EffectProcessing();

	void AllHandLack();

	bool CardConfirmation();


	void RandomHandDeath(int num);

	std::vector<Card*> SelectionHand(int num);

private:
	// シャッフルのための乱数エンジンを用意
	std::mt19937 g;  // メルセンヌ・ツイスタ（高品質な乱数生成）

	std::vector<std::unique_ptr<Card>> sDeck;
	std::vector<std::unique_ptr<Card>> deck;
	std::vector<std::unique_ptr<Card>> cemetery;
	std::vector<std::unique_ptr<Card>> handCard;
	std::vector<std::unique_ptr<Card>> execution;

	std::vector<int> nnnum;

	std::vector<Card*> deckDisplay;
	std::vector<Card*> executionDisplay;
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


	const Vector2 deckButtonPos = {100.0f, 600.0f};
	const Vector2 deckButtonSize = {40.0f, 40.0f};

	std::unique_ptr<Button> deckButton;

	bool isDeck = false;

	const Vector2 cemeteryButtonPos = {1280.0f - 100.0f, 600.0f};
	const Vector2 cemeteryButtonSize = {40.0f, 40.0f};

	std::unique_ptr<Button> cemeteryButton;


	const Vector2 selectHandButtonPos = {640.0f, 400.0f};
	const Vector2 selectHandButtonSize = {120.0f, 40.0f};

	std::unique_ptr<Button> selectHandButton;
	bool isCemetery = false;

	Sprite sprite;
	uint32_t TH;

	bool isReverseButton = false;

	EnemyManager* enemyManager = nullptr;

	Player* player_ = nullptr;

	NumberSprite number;




	bool isSelectionHand = false;
	bool isSelectOK = false;
};
