#include "Node.h"

using namespace MathUtility;

void Node::Initialize() {
	sprite.Initialize();
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize({20.0f, 20.0f});
	TH = TextureManager::GetInstance()->Load("circle.png");
}

void Node::Updata() {
	senn.clear();

	int tennCount = 10;

	for (Node* node : nextNodes) {
		for (int i = 0; i < tennCount; i++) {
			Sprite sp;
			sp.Initialize();
			sp.SetTextureHandle(TH);
			sp.SetAnchorPoint({0.5f, 0.5f});
			sp.SetSize({5.0f, 5.0f});
			sp.SetColor({0.0f, 0.0f, 0.0f, 1.0f});
			Vector2 pos = GetSpritePos();
			Vector2 nextPos = node->GetSpritePos();

			
			sp.SetPosition(Vector2Lerp(pos, nextPos, static_cast<float>(i) / static_cast<float>(tennCount)));

			senn.push_back(sp);
		}
	}

}

void Node::Draw() {
	for (Sprite sp : senn) {
		sp.Draw();
	}
	sprite.Draw();
}

void Node::SetNodeType(NodeType nodeType) {
	nodeType_ = nodeType;
	uint32_t th=0;
	th;
	TextureManager* tm = TextureManager::GetInstance();
	tm;
	switch (nodeType_) {
	case NodeType::Enemy:
		//th = tm->Load("");
		//sprite.SetTextureHandle(th);
		sprite.SetColor({1.0f, 1.0f, 1.0f, 1.0f});
		break;
	case NodeType::Elite:
		sprite.SetColor({1.0f, 0.0f, 0.0f, 1.0f});
		break;
	case NodeType::Rest:
		sprite.SetColor({1.0f, 0.4f, 0.0f, 1.0f});
		
		break;
	case NodeType::Treasure:
		sprite.SetColor({1.0f, 1.0f, 0.0f, 1.0f});
		
		break;
	case NodeType::Shop:
		sprite.SetColor({1.0f, 0.0f, 1.0f, 1.0f});
		break;
	case NodeType::Event:
		sprite.SetColor({0.0f, 1.0f, 1.0f, 1.0f});
		break;
	case NodeType::Boss:
		sprite.SetColor({0.0f, 0.0f, 0.0f, 1.0f});
		break;
	}

}

