#include "MapManager.h"
#include <iostream>
#include <algorithm>
#include <functional>

void MapManager::Initialize() {
	std::random_device rd; // 乱数の種
	g.seed(rd());
	maxfloar = 10;
	maxNode = 7;
	branchChance = 50;
}

void MapManager::Update() {
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		CreateMap();
	}
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] != nullptr) {
				map[i][j]->SetSpritePos({640.0f - (100.0f * ((map[i].size() - 1) / 2.0f - j)), 720.0f - 70.0f * i - 70.0f});
			}
		}
	}
	for (const auto& nodes : map) {
		for (const auto& node : nodes) {
			if (node != nullptr) {
				node->Updata();
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
				node->id = id;
				id++;
				map[j][nodeX] = std::move(node);
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
	

	if (i <= 50) return NodeType::Enemy;
	if (i <= 60) return NodeType::Elite;
	if (i <= 70) return NodeType::Rest;
	if (i <= 80) return NodeType::Treasure;
	if (i <= 90) return NodeType::Shop;

	
	return NodeType::Event;
}
