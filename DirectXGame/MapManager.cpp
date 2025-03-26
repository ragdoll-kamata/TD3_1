#include "MapManager.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

void MapManager::Initialize() {
	std::random_device rd; // 乱数の種
	g.seed(rd());
	maxfloar = 16;
	maxNode = 7;
}

void MapManager::Update() {
	if (Input::GetInstance()->IsTriggerMouse(0)) {
		CreateMap();
	}

	scroll = static_cast<float>(Input::GetInstance()->GetWheel()) / 3.0f;




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

void MapManager::Draw() {
	for (const auto& nodes : map) {
		for (const auto& node : nodes) {
			if (node != nullptr) {
				node->Draw();
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
				prevNodeType = node->nodeType_;
				node->id = id;
				id++;
				map[j][nodeX] = std::move(node);
			} else {
				if (prevNodeType == map[j][nodeX]->nodeType_) {
					if (prevNodeType != NodeType::Enemy && prevNodeType != NodeType::Event) {
						map[j - 1][prevNodeX]->SetNodeType(ReGetRandomNodeType(j - 1, prevNodeX));
					}
				}
				prevNodeType = map[j][nodeX]->nodeType_;
			}

			// ルートを繋ぐ
			if (j != 0) {
				bool is = false;
				for (Node* node : map[j - 1][prevNodeX]->nextNodes) {
					if (node->id == map[j][nodeX]->id) {
						is = true;
					}
				}
				if (!is) {
					map[j - 1][prevNodeX]->nextNodes.push_back(map[j][nodeX].get());
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
						for (Node* node : map[j][nodeX - 1]->nextNodes) {
							if (map[j + 1][nodeX] != nullptr) {
								if (node->id == map[j + 1][nodeX]->id) {
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
						for (Node* node : map[j][nodeX + 1]->nextNodes) {
							if (map[j + 1][nodeX] != nullptr) {
								if (node->id == map[j + 1][nodeX]->id) {
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

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] != nullptr) {
				map[i][j]->SetSpritePos({640.0f - (100.0f * ((map[i].size() - 1) / 2.0f - j)), 720.0f - 70.0f * i - 70.0f});
			}
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

	if (IsRandomNodeType(evectProbability, i, 3, NodeType::Null, 10)) {
		return NodeType::Event;
	}
	
	return NodeType::Enemy;
}

NodeType MapManager::ReGetRandomNodeType(int floor, int x) {
	int Lastfloor = maxfloar - 1;

	std::unordered_map<NodeType, bool> nodeTypes;
	for (Node* node : map[floor][x]->nextNodes) {
		if (!nodeTypes.contains(node->nodeType_)) {
			nodeTypes.insert({node->nodeType_, false});
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

	if (IsRandomNodeType(evectProbability, i, 3, NodeType::Null, 10)) {
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
