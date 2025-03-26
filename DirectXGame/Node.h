#pragma once
#include <KamataEngine.h>
#include <vector>
using namespace KamataEngine;
enum class NodeType {
	Enemy,
	Elite,
	Rest,
	Treasure,
	Shop,
	Event,
	Boss,
	Null,
};

class Node {
public:

	void Initialize();

	void Updata();

	void ScrollUpdata();

	void Draw();

	void SetSpritePos(Vector2 pos) { kSPos = pos; }
	void SetScroll(Vector2 s);

	void SetNodeType(NodeType nodeType);

	Vector2 GetSpritePos() const;

	Sprite sprite;
	NodeType nodeType_;
	int id;
	std::vector<Node*> nextNodes;
	std::vector<Sprite> senn;
	uint32_t TH;
	Vector2 sPos;
	Vector2 kSPos;
	Vector2 scroll;
	Vector2 preScroll;

	int timer;
	const int kTimer = 10;
};
