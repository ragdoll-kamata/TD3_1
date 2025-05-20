#pragma once
#include <KamataEngine.h>
#include "Button.h"
#include <vector>

using namespace KamataEngine;

class CardManager;
class MapManager;
class Player;
class Card;

class UIManager {
public:

	void Initialize(Player* player, CardManager* cardManager, MapManager* mapManager);

	void Update();

	void Draw();

	bool IsSDeckOpen() const { return isSDeckOpen; }

private:
	Sprite uiBack;
	Sprite back; 
	Player* player_ = nullptr;
	CardManager* cardManager_ = nullptr;
	MapManager* mapManager_ = nullptr;

	bool isSDeckOpen = false;

	std::vector<Card*> sCard;
	std::vector<Vector2> sPos;

	Button map;
	Button kDeck;

	float scroll;
	float prevWheel;
};
