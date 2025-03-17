#include "Dummy.h"
#include "ActionFactory.h"
using namespace MathUtility;
void Dummy::Initialize() {
	TH = TextureManager::GetInstance()->Load("white1x1.png");
	sprite.Initialize();
	sprite.SetTextureHandle(TH);
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize({60.0f, 60.0f});
	sprite.SetColor({1.0f,0.5f,0.0f,1.0f,});
	sprite.SetPosition({640.0f,320.f});
	halfSize = {60.0f, 60.0f};

	status_ = std::make_unique<Status>();
	status_->Initialize({640.0f, 320.f}, halfSize, 999);

	halfSize /= 2.0f;
}

void Dummy::PredictNextAction() {
	if (index == 0) {
		enemyAction = ActionFactory::CreateAction("Atack");
		enemyAction->Initialize(status_.get(), 5);
		enemyAction->SetBattleManager(battleManager_);
		index = 1;
	} else {
		enemyAction = ActionFactory::CreateAction("Shield");
		enemyAction->Initialize(status_.get(), 5, 0, this);
		enemyAction->SetBattleManager(battleManager_);
		index = 0;
	}
}

void Dummy::StartBattlePeculiar() {}
