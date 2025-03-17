#pragma once
#include <memory>
#include "NumberSprite.h"
#include "Status.h"
class Player {
public:
	void Initialize();

	void Update();

	void Draw();

	Status* GetStatus() { return status_.get(); }

private:
	std::unique_ptr<Status> status_;
};
