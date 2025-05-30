#pragma once
#include <memory>
#include "NumberSprite.h"
#include "Status.h"
class Player {
public:
	void Initialize();

	void Update();

	void Draw();

	void EndBattle();

	Status* GetStatus() { return status_.get(); }

	void Rest();

private:
	std::unique_ptr<Status> status_;
};
