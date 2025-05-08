#include "EventManager.h"
#include "TreasureEvent.h"
void EventManager::Update() {
	if (event) {
		event->Update();
		if (event->IsEnd()) {
			event.reset();
		}
	}
}

void EventManager::Draw() {
	if (event) {
		event->Draw();
	}
}

void EventManager::CreateTreasureEvent() {
	event = std::make_unique<TreasureEvent>();
	event->Initialize();
}
