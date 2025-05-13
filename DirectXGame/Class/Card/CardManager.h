#pragma once
#include <memory>
#include <vector>
#include <random>
#include <KamataEngine.h>
#include <unordered_map>
#include <functional>


#include "Card.h"
#include "Button.h"
#include "numberSprite.h"
#include "CardFactory.h"

class EnemyManager;
class BattleManager;
class RelicManager;
class Player;

using namespace KamataEngine;
class CardManager {
public:

	void Initialize(EnemyManager* enemy, Player* player);
	void BattleUpdata();

	void DrawBattle();

	bool StartBattleTrue();

	bool StartMainTurn();

	bool MainTurn();

	bool EndMainTurn();

	void StartBattle();

	bool EndBattleTrue();

	void EndBattle();
	
private:
	/// <summary>
	/// デッキシャッフル
	/// </summary>
	void DeckShuffle();

	/// <summary>
	/// デッキリフレッシュ
	/// </summary>
	void DeckRefresh();

	/// <summary>
	/// カード効果処理
	/// </summary>
	void EffectProcessing();

	/// <summary>
	/// ハンドラック計算
	/// </summary>
	void AllHandLack();

	bool CardConfirmation();

	void HandCardSetSpritePos(int i, Vector2 pos, float t = 0.11f);

	void CardLocationUpdate();

	void CardLocationMove(std::unique_ptr<Card> card, CardLocation cardLocation);

	void CardDrawMove();

public:
	/// <summary>
	/// カードドロー
	/// </summary>
	/// <param name="num">ドロー枚数</param>
	void CardDraw(int num);

	/// <summary>
	/// ランダム手札破壊!
	/// </summary>
	/// <param name="num">破壊する数</param>
	/// <returns>破壊できなかった数</returns>
	int RandomHandDeath(int num);

	/// <summary>
	/// 手札からカードの取得
	/// </summary>
	/// <param name="num">枚数</param>
	/// <param name="isMaxSelect">枚数分選ぶ必要があるか</param>
	/// <returns>選択カード</returns>
	std::vector<Card*> SelectionHand(int num, bool isMaxSelect);

	/// <summary>
	/// 使用したカードのタイプを取得
	/// </summary>
	/// <returns>カードタイプ</returns>
	CardType GetExecutionCardType() { return executionCardType; }

	/// <summary>
	/// 初期デッキ生成
	/// </summary>
	void StartCreateSDeck();

	void SetBattleManager(BattleManager* battleManager) { battleManager_ = battleManager; }
	void SetRelicManager(RelicManager* relicManager) { relicManager_ = relicManager; }

	std::vector<std::unique_ptr<Card>> RewardCardGeneration();

	void AddSDeck(std::unique_ptr<Card> c) { sDeck.push_back(std::move(c)); }


	std::vector<Card*> GetSDeck();

	void AddDrawNum(int num) { drawNum += num; }
	std::unique_ptr<Card> CardLottery();

private:
	std::unique_ptr<CardFactory> cardFactory_ = nullptr;

	// シャッフルのための乱数エンジンを用意
	std::mt19937 g;  // メルセンヌ・ツイスタ（高品質な乱数生成）

	std::vector<std::unique_ptr<Card>> sDeck;
	std::vector<std::unique_ptr<Card>> deck;
	std::vector<std::unique_ptr<Card>> cemetery;
	std::vector<std::unique_ptr<Card>> handCard;
	std::vector<std::unique_ptr<Card>> execution;
	std::vector<std::unique_ptr<Card>> exclusion;

	CardType executionCardType;

	std::vector<int> nnnum;

	std::vector<Card*> deckDisplay;
	std::vector<Card*> executionDisplay;
	std::vector<Vector2> sPos;
	float scroll;
	float prevWheel;

	int handLack;
	int playerLack;

	int holdH;
	bool isHold;

	int drawNum = 5;
	int drawIndex = 0;

	const Vector2 turnEndButtonPos = {1100.0f, 500.0f};
	const Vector2 turnEndButtonStandbyPos = {1400.0f, 500.0f};
	const Vector2 turnEndButtonSize = {160.0f, 40.0f};

	const Vector2 allReverseButtonSize = {120.0f, 40.0f};
	const Vector2 allReverseYssButtonPos = {640.0f - allReverseButtonSize.x / 2.0f - 20.0f, 360.0f};
	const Vector2 allReverseNoButtonPos = {640.0f + allReverseButtonSize.x / 2.0f + 20.0f, 360.0f};

	std::unique_ptr<Button> turnEndButton;
	std::unique_ptr<Button> allReverseYssButton;
	std::unique_ptr<Button> allReverseNoButton;


	const Vector2 deckButtonPos = {100.0f, 600.0f};
	const Vector2 deckButtonStandbyPos = {-200.0f, 600.0f};
	const Vector2 deckButtonSize = {40.0f, 40.0f};

	std::unique_ptr<Button> deckButton;

	bool isDeck = false;

	const Vector2 cemeteryButtonPos = {1280.0f - 100.0f, 600.0f};
	const Vector2 cemeteryButtonStandbyPos = {1280.0f - 100.0f + 300.0f, 600.0f};
	const Vector2 cemeteryButtonSize = {40.0f, 40.0f};

	std::unique_ptr<Button> cemeteryButton;


	const Vector2 selectHandButtonPos = {640.0f, 400.0f};
	const Vector2 selectHandButtonSize = {120.0f, 40.0f};

	std::unique_ptr<Button> selectHandButton;
	bool isCemetery = false;

	Sprite sprite;
	uint32_t TH;

	bool isReverseButton = false;

	BattleManager* battleManager_ = nullptr;

	EnemyManager* enemyManager = nullptr;

	RelicManager* relicManager_ = nullptr;

	Player* player_ = nullptr;

	NumberSprite number;
	const Vector2 numberPos = {100.0f, 500.0f};
	const Vector2 numberStandbyPos = {100.0f - 300.0f, 500.0f};



	bool isSelectionHand = false;
	bool isSelectOK = false;

	const int kStartTimer = 60;
	int startTimer;

	const int kEndTimer = 20;
	int endTimer;

	bool isStartRelic = false;

	uint32_t cardDrawSH = 0;
	uint32_t cardShuffleSH = 0;


	uint32_t cardDrawNum = 0;

	const int kCardDrawTimer = 10;
	int cardDrawTimer = 0;

	const int kCardShuffleTimer = 60;
	int cardShuffleTimer = 0;


	const int kUncommonChanceValue = 37;
	const int kStartRareChanceValue = -5;
	const int kUpRareChanceValue = 1;

	int rareChanceValue = kStartRareChanceValue;


};
