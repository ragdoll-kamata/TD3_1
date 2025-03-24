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
};

class Node {
public:

	void Initialize();

	void Updata();

	void Draw();

	void SetSpritePos(Vector2 pos) { sprite.SetPosition(pos); }

	void SetNodeType(NodeType nodeType);

	Vector2 GetSpritePos() const { return sprite.GetPosition(); }

	Sprite sprite;
	NodeType nodeType_;
	int id;
	std::vector<Node*> nextNodes;
	std::vector<Sprite> senn;
	uint32_t TH;
};
