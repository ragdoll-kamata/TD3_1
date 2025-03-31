#pragma once
#include <KamataEngine.h>
#include <list>
#include <vector>
#include <memory>
#include "math/Vector4.h"
using namespace KamataEngine;

class MapManager;

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

	void SetKSpritePos(Vector2 pos) { kSPos = pos; }
	Vector2 GetKSpritePos() const { return kSPos; }
	void SetSpritePos(Vector2 pos) { sPos = pos; }
	void SetScroll(Vector2 s);



	void CreateDottedLine();
	Vector2 GetSpritePos() const;

	void ReSetScroll();

	bool IsOnCollision(Vector2 pos) ;

	void SetBrightness(float s) { brightness = s; }
	void SetTransparency(float s) { transparency = s; }

	void SetIsSelect(bool a) { isSelect = a; }


	std::vector<Node*> GetNextNodes() const { return nextNodes; }
	void SetNextNodes(Node* node) { nextNodes.push_back(node); }

	NodeType GetNodeType() const { return nodeType_; }
	void SetNodeType(NodeType nodeType);

	int GetId() const { return id_; }
	void SetId(int id) { id_ = id; }

	void SetMapManager(MapManager* mapManager) { mapManager_ = mapManager; }


	bool IsExplored() const { return isExplored; }

private:
	MapManager* mapManager_ = nullptr;

	Sprite sprite;
	Sprite sprite2;
	NodeType nodeType_;
	int id_;
	std::vector<Node*> nextNodes;
	std::vector<std::vector<std::unique_ptr<Sprite>>> senn;
	uint32_t TH;
	Vector2 sPos;
	Vector2 kSPos;
	Vector2 scroll;
	Vector2 kSize;

	int tennCount = 10;

	Vector4 color;
	float brightness = 1.0f;
	float transparency = 1.0f;

	bool isSelect = false;
	bool isExplored = false;

	bool isA = true;
	float size = 1.0f;

	const int kTimer = 60;
	int timer = kTimer;
	
};
