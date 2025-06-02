#include "Caterpillar.h"

#include "ActionFactory.h"
using namespace MathUtility;
void Caterpillar::Initialize() {
	Enemy::Initialize();
	TH = TextureManager::GetInstance()->Load("white1x1.png");
	sprite.Initialize();
	sprite.SetTextureHandle(TH);
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize({90.0f, 60.0f});
	sprite.SetColor({
	    1.0f,
	    0.5f,
	    0.0f,
	    1.0f,
	});
	sprite.SetPosition({640.0f, 320.f});
	halfSize = {90.0f, 60.0f};

	status_ = std::make_unique<Status>();
	status_->Initialize({640.0f, 320.f}, halfSize, 45);

	halfSize /= 2.0f;
}

void Caterpillar::PredictNextAction() {
	int ra = dist(g);
	if (ra <= 75 || index == 1) {
		std::uniform_int_distribution<int> a(5, 8);
		enemyAction = ActionFactory::CreateAction("Atack");
		enemyAction->Initialize(status_.get(), a(g));
		enemyAction->SetBattleManager(battleManager_);
		index = 0;
	} else {
		std::uniform_int_distribution<int> a(3, 8);
		enemyAction = ActionFactory::CreateAction("DebuffAttack");
		enemyAction->Initialize(status_.get(), a(g));
		enemyAction->SetStatusEffectName("Weakening");
		enemyAction->SetStack(2);
		enemyAction->SetBattleManager(battleManager_);
		index = 1;
	}

}

void Caterpillar::StartBattlePeculiar() {}