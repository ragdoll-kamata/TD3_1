#include "Node.h"
#include "MapManager.h"
#include <algorithm>

using namespace MathUtility;

void Node::Initialize() {
	sprite.Initialize();
	kSize = {20.0f, 20.0f};
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize(kSize);
	TH = TextureManager::GetInstance()->Load("circle.png");
	sprite2.Initialize();
	sprite2.SetAnchorPoint({0.5f, 0.5f});
	sprite2.SetSize(kSize * 1.4f);
	sprite2.SetColor({0.0f, 0.0f, 0.0f, 1.0f});
}

void Node::Updata() {
	if (isSelect && mapManager_->GetIsMove()) {
		if (isA) {
			timer--;
			if (timer <= 0) {
				isA = false;
			}
		} else {
			timer++;
			if (timer >= kTimer) {
				isA = true;
			}
		}
		size = Lerp(1.0f, 1.7f, static_cast<float>(timer) / static_cast<float>(kTimer));
	} else {
		size = 1.0f;
	}
	

	sprite.SetSize(kSize * size);

	sPos = Vector2Lerp(sPos, kSPos + scroll, 0.1f);


	sprite.SetPosition(GetSpritePos());
	sprite.SetColor(Vector4(color.x * brightness, color.y * brightness, color.z * brightness, color.w * transparency));
	sprite2.SetPosition(GetSpritePos());
	sprite2.SetColor(Vector4(0.0f, 0.0f, 0.0f, color.w * transparency));
}

void Node::ScrollUpdata() {

	for (int i = 0; i < senn.size(); i++) {
		for (int j = 0; j < senn[i].size(); j++) {
			Vector2 pos = GetSpritePos();
			Vector2 nextPos = nextNodes[i]->GetSpritePos();
			senn[i][j]->SetPosition(Vector2Lerp(pos, nextPos, static_cast<float>(j) / static_cast<float>(tennCount)));
			senn[i][j]->SetColor({0.0f, 0.0f, 0.0f, transparency});
		}
	}
}

void Node::Draw() {

	for (int i = 0; i < senn.size(); i++) {
		for (const auto& sp : senn[i]) {
			sp->Draw();
		}
	}
	if (isExplored) {
		sprite2.Draw();
	}
	sprite.Draw();
	
}

void Node::SetScroll(Vector2 s) {
	scroll = s;
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
		color = {1.0f, 1.0f, 1.0f, 1.0f};
		break;
	case NodeType::Elite:
		color = {1.0f, 0.0f, 0.0f, 1.0f};
		break;
	case NodeType::Rest:
		color = {1.0f, 0.4f, 0.0f, 1.0f};
		
		break;
	case NodeType::Treasure:
		color = {1.0f, 1.0f, 0.0f, 1.0f};
		
		break;
	case NodeType::Shop:
		color = {1.0f, 0.0f, 1.0f, 1.0f};
		break;
	case NodeType::Event:
		color = {0.0f, 1.0f, 1.0f, 1.0f};
		break;
	case NodeType::Boss:
		color = {0.0f, 0.0f, 0.0f, 1.0f};
		break;
	}

}

void Node::CreateDottedLine() {
	senn.clear();
	senn.resize(nextNodes.size());
	int j = 0;
	for (Node* node : nextNodes) {
		for (int i = 0; i < tennCount; i++) {
			std::unique_ptr<Sprite> sp(new Sprite);
			sp->Initialize();
			sp->SetTextureHandle(TH);
			sp->SetAnchorPoint({0.5f, 0.5f});
			sp->SetSize({5.0f, 5.0f});
			sp->SetTextureRect({}, {64.0f, 64.0f});
			sp->SetColor({0.0f, 0.0f, 0.0f, 1.0f});
			Vector2 pos = GetSpritePos();
			Vector2 nextPos = node->GetSpritePos();

			sp->SetPosition(Vector2Lerp(pos, nextPos, static_cast<float>(i) / static_cast<float>(tennCount)));

			senn[j].push_back(std::move(sp));
		}
		j++;
	}
	senn;
}

Vector2 Node::GetSpritePos() const { return sPos; }

void Node::ReSetScroll() { sPos = kSPos + scroll; }

bool Node::IsOnCollision(Vector2 pos) {
	if (isSelect) {

		Vector2 hPos{
		    std::clamp(pos.x, sprite.GetPosition().x - 10.0f * 1.5f, sprite.GetPosition().x + 10.0f * 1.5f),
		    std::clamp(pos.y, sprite.GetPosition().y - 10.0f * 1.5f, sprite.GetPosition().y + 10.0f * 1.5f),
		};

		hPos.x -= pos.x;
		hPos.y -= pos.y;
		float len = MathUtility::Length(hPos);
		if (len <= 0.0f) {
			for (Node* node : nextNodes) {
				node->SetIsSelect(true);
			}
			isExplored = true;
			return true;
		}
	}
	return false;
}

