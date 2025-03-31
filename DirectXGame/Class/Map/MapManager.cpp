#include "MapManager.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include "BattleManager.h"
#include "RewardManager.h"
#include "Easings.h"
using namespace MathUtility;
void MapManager::Initialize(BattleManager* battleManager, RewardManager* rewardManager) {
	std::random_device rd; // 乱数の種
	g.seed(rd());
	maxfloar = 16;
	maxNode = 7;
	back.Initialize();
	back.SetSize({1280.0f, 720.0f});
	back.SetColor({0.0f, 0.0f, 0.0f, 0.9f});

	mapBack.Initialize();
	mapBack.SetSize({100.0f * (maxNode + 1), verticalNodeSpace * (maxfloar)});
	mapBack.SetColor({0.5f, 0.5f, 0.5f, 1.0f});
	mapBack.SetAnchorPoint({0.5f, 1.0f});
	mapBackPos = {640.0f, 720.0f - 50.0f};
	mapBack.SetPosition(mapBackPos);

	battleManager_ = battleManager;
	rewardManager_ = rewardManager;
	displayOpenMapTimer = kDisplayMapTimer + 1;
	displayCloseMapTimer = kDisplayMapTimer + 1;
}

void MapManager::Update() {
	float mouseWheel = static_cast<float>(Input::GetInstance()->GetWheel()) / 3.0f - prevWheel;
	prevWheel = static_cast<float>(Input::GetInstance()->GetWheel()) / 3.0f;
	if (displayCloseMapTimer <= kDisplayMapTimer) {
		float t = static_cast<float>(displayCloseMapTimer) / static_cast<float>(kDisplayMapTimer);

		back.SetColor({0.0f, 0.0f, 0.0f, Lerp(0.9f, 0.0f, t)});
		mapBack.SetColor({0.5f, 0.5f, 0.5f, Lerp(1.0f, 0.0f, t)});
		for (const auto& nodes : map) {
			for (const auto& node : nodes) {
				if (node != nullptr) {
					node->SetTransparency(Lerp(1.0f, 0.0f, t));
				}
			}
		}

		displayCloseMapTimer++;
	} 
	if (isMapOpen) {
		if (displayOpenMapTimer <= kDisplayMapTimer) {
			float t = static_cast<float>(displayOpenMapTimer) / static_cast<float>(kDisplayMapTimer);
			
			back.SetColor({0.0f, 0.0f, 0.0f, Lerp(0.0f, 0.9f, t)});
			mapBack.SetColor({0.5f, 0.5f, 0.5f, Lerp(0.0f, 1.0f, t)});
			for (const auto& nodes : map) {
				for (const auto& node : nodes) {
					if (node != nullptr) {
						node->SetTransparency(Lerp(0.0f, 1.0f, t));
					}
				}
			}

			displayOpenMapTimer++;
		} 

		if (displayOpenMapTimer >= kDisplayMapTimer) {
			if (startblankTimer > 0) {
				float t = static_cast<float>(startMapTimer) / static_cast<float>(kStartMapTimer);

				startScroll = Lerp(0.0f, verticalNodeSpace * (maxfloar + 1) - 720.0f, Easings::EaseOutQuart(t));
				startMapTimer--;

				scroll = startScroll;
				if (startMapTimer <= 0) {
					startMapTimer = 0;
					startblankTimer--;
				}

			} else {
				scroll += mouseWheel;
				scroll = std::clamp<float>(scroll, 0.0f, verticalNodeSpace * (maxfloar + 1) - 720.0f);
			}
		}
	}
	mapBack.SetPosition(Vector2Lerp(mapBack.GetPosition(), {mapBackPos.x, mapBackPos.y + scroll}, 0.1f));
	for (const auto& nodes : map) {
		for (const auto& node : nodes) {
			if (node != nullptr) {
				node->SetScroll({0.0f, static_cast<float>(scroll)});
				node->Updata();
			}
		}
	}
	for (const auto& nodes : map) {
		for (const auto& node : nodes) {
			if (node != nullptr) {
				node->ScrollUpdata();
			}
		}
	}
}
void MapManager::CollisionUpdata() {
	if (startblankTimer <= 0) {
		Vector2 mousePos = Input::GetInstance()->GetMousePosition();
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			CreateMap();
		}
		if (isMove) {
			if (Input::GetInstance()->IsTriggerMouse(0)) {
				for (const auto& node : map[selectfloar]) {
					if (node != nullptr) {
						if (node->IsOnCollision(mousePos)) {
							for (const auto& node2 : map[selectfloar]) {
								if (node2 != nullptr) {
									if (!node2->IsExplored()) {
										node2->SetBrightness(0.2f);
									}
									node2->SetIsSelect(false);
								}
							}

							switch (node->GetNodeType()) {
							case NodeType::Enemy:
								SetIsMapOpen(false);
								battleManager_->StartBattle();
								break;
							case NodeType::Elite:
								break;
							case NodeType::Rest:
								break;
							case NodeType::Treasure:
								break;
							case NodeType::Shop:
								break;
							case NodeType::Event:
								break;
							case NodeType::Boss:
								break;
							}
							rewardManager_->ClearReward();
							displayOpenMapTimer = 0;
							if (selectfloar < maxfloar - 1) {
								selectfloar++;
							}
						}
					}
				}
			}
		}
	}
}

void MapManager::Draw() {
	if (true) {
		back.Draw();
		mapBack.Draw();
		for (const auto& nodes : map) {
			for (const auto& node : nodes) {
				if (node != nullptr) {
					node->Draw();
				}
			}
		}
	}
}

void MapManager::CreateMap() {

	// 初期化
	map.clear();
	map.resize(maxfloar);
	
	for (int i = 0; i < maxfloar; i++) {
		for (int j = 0; j < maxNode; j++) {
			 map[i].push_back(nullptr);
		}
	}

	int id = 0;

	// rootの回数、マップのルートを生成する
	for (int i = 0; i < root; i++) {
		// 初期位置
		int prevNodeX = -1;
		int nodeX = maxNode / 2;
		std::uniform_int_distribution<int> bure(-1,1);
		nodeX += bure(g);

		for (int j = 0; j < maxfloar; j++) {

			// まだノードが作られていないなら作る
			if (map[j][nodeX] == nullptr) {
				std::unique_ptr<Node> node = std::make_unique<Node>();
				node->Initialize();

				node->SetNodeType(GetRandomNodeType(j));
				prevNodeType = node->GetNodeType();

				node->SetId(id);
				id++;

				node->SetMapManager(this);

				map[j][nodeX] = std::move(node);
			} else {
				if (prevNodeType == map[j][nodeX]->GetNodeType()) {
					if (prevNodeType != NodeType::Enemy && prevNodeType != NodeType::Event) {
						map[j - 1][prevNodeX]->SetNodeType(ReGetRandomNodeType(j - 1, prevNodeX));
					}
				}
				prevNodeType = map[j][nodeX]->GetNodeType();
			}

			// ルートを繋ぐ
			if (j != 0) {
				bool is = false;
				for (Node* node : map[j - 1][prevNodeX]->GetNextNodes()) {
					if (node->GetId() == map[j][nodeX]->GetId()) {
						is = true;
					}
				}
				if (!is) {
					map[j - 1][prevNodeX]->SetNextNodes(map[j][nodeX].get());
				}
			}

			// 次のルート設定

			if (j < maxfloar - 1) {

				int no = 0;

				if (j >= maxfloar - maxNode / 2 - 1) {
					no = j - (maxfloar - maxNode / 2 - 1) + 1;
				}

				std::vector<int> possibleNodes;
				if (nodeX >= 0 + no && nodeX < maxNode - no) {
					possibleNodes.push_back(nodeX);
				}

				if (nodeX - 1 >= 0 + no) {
					bool is = false;
					if (map[j][nodeX - 1] != nullptr) {
						for (Node* node : map[j][nodeX - 1]->GetNextNodes()) {
							if (map[j + 1][nodeX] != nullptr) {
								if (node->GetId() == map[j + 1][nodeX]->GetId()) {
									is = true;
								}
							}
						}
					}
					if (!is) {
						possibleNodes.push_back(nodeX - 1);
					}
				}

				if (nodeX + 1 < maxNode - no) {
					bool is = false;
					if (map[j][nodeX + 1] != nullptr) {
						for (Node* node : map[j][nodeX + 1]->GetNextNodes()) {
							if (map[j + 1][nodeX] != nullptr) {
								if (node->GetId() == map[j + 1][nodeX]->GetId()) {
									is = true;
								}
							}
						}
					}
					if (!is) {
						possibleNodes.push_back(nodeX + 1);
					}
				}
				std::uniform_int_distribution<int> nextDist(0, static_cast<int>(possibleNodes.size()) - 1);
				prevNodeX = nodeX;
				nodeX = possibleNodes[nextDist(g)];
			}
		}
	}
	std::uniform_real_distribution<float> radomShake(-30.0f, 30.0f);
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] != nullptr) {
				Vector2 shake = {radomShake(g), radomShake(g)};
				Vector2 pos = {640.0f - (100.0f * ((map[i].size() - 1) / 2.0f - j)), 720.0f - verticalNodeSpace * i - verticalNodeSpace};

				map[i][j]->SetKSpritePos(pos + shake);
				map[i][j]->ReSetScroll();
			}
		}
	}
	startMapTimer = kStartMapTimer;
	startblankTimer = kStartblankTimer;
	startScroll = verticalNodeSpace * (maxfloar + 1) - 720.0f;


	mapBack.SetPosition({mapBackPos.x, mapBackPos.y + startScroll});

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] != nullptr) {
				Vector2 a = map[i][j]->GetKSpritePos();
				map[i][j]->SetSpritePos({a.x, a.y + startScroll});
				map[i][j]->CreateDottedLine();
			}
		}
	}
	selectfloar = 0;
	for (const auto& node : map[selectfloar]) {
		if (node != nullptr) {
			node->SetIsSelect(true);
		}
	}


	

}

void MapManager::SetIsMapOpen(bool is) { 
	if (isMapOpen != is) {
		isMapOpen = is;
		if (isMapOpen) {
			displayOpenMapTimer = 0;
		} else {
			displayCloseMapTimer = 0;
		}
	}
}

NodeType MapManager::GetRandomNodeType(int floor) { 
	int Lastfloor = maxfloar - 1;
	if (floor == 0) {
		return NodeType::Enemy;
	} 
	if (floor == Lastfloor) {
		return NodeType::Boss;
	} 
	if (floor == Lastfloor - 1) {
		return NodeType::Rest;
	}


	std::uniform_int_distribution<int> get_rand_uni_int(1, 100);
	int i = get_rand_uni_int(g);

	if (floor > 2) {
		if (IsRandomNodeType(eliteProbability, i, 3, NodeType::Elite)) {
			return NodeType::Elite;
		}
	}

	if (floor > 2 && floor < Lastfloor - 2) {
		if (IsRandomNodeType(restProbability, i, 3, NodeType::Rest)) {
			return NodeType::Rest;
		}
	}

	if (IsRandomNodeType(treasureProbability, i, 3, NodeType::Treasure)) {
		return NodeType::Treasure;
	}

	if (IsRandomNodeType(shopProbability, i, 3, NodeType::Shop)) {
		return NodeType::Shop;
	}

	if (IsRandomNodeType(evectProbability, i, 3, NodeType::Null, 15)) {
		return NodeType::Event;
	}
	
	return NodeType::Enemy;
}

NodeType MapManager::ReGetRandomNodeType(int floor, int x) {
	int Lastfloor = maxfloar - 1;

	std::unordered_map<NodeType, bool> nodeTypes;
	for (Node* node : map[floor][x]->GetNextNodes()) {
		if (!nodeTypes.contains(node->GetNodeType())) {
			nodeTypes.insert({node->GetNodeType(), false});
		}
	}

	x;
	std::uniform_int_distribution<int> get_rand_uni_int(1, 100);
	int i = get_rand_uni_int(g);

	if (floor > 2) {
		if (nodeTypes.contains(NodeType::Elite)) {
			if (IsRandomNodeType(eliteProbability, i, 3, NodeType::Elite, 5)) {
				return NodeType::Elite;
			}
		}
	}

	if (floor > 2 && floor < Lastfloor - 2) {
		if (nodeTypes.contains(NodeType::Rest)) {
			if (IsRandomNodeType(restProbability, i, 3, NodeType::Rest)) {
				return NodeType::Rest;
			}
		}
	}

	if (nodeTypes.contains(NodeType::Treasure)) {
		if (IsRandomNodeType(treasureProbability, i, 3, NodeType::Treasure)) {
			return NodeType::Treasure;
		}
	}

	if (nodeTypes.contains(NodeType::Shop)) {
		if (IsRandomNodeType(shopProbability, i, 3, NodeType::Shop)) {
			return NodeType::Shop;
		}
	}

	if (IsRandomNodeType(evectProbability, i, 3, NodeType::Null, 15)) {
		return NodeType::Event;
	}

	return NodeType::Enemy;
}

bool MapManager::IsRandomNodeType(int& probability, int& i, const int plus, NodeType nodeType, const int& kProbability) {
	if (nodeType != prevNodeType) {
		if (i <= probability + kProbability) {
			probability = 0;
			return true;
		}
	}
	i -= probability;
	probability += plus;
	return false;
}
