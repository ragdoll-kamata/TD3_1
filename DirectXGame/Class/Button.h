#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
class Button {
public:

	void Initialize(const Vector2& pos, const Vector2& size, std::string name, Vector4 color);

	void Draw();

	bool IsOnCollision(Vector2 pos);

	void SetPosition(Vector2 pos) { sprite.SetPosition(pos); }

protected:
	Sprite sprite;
	uint32_t TH;

	Vector2 halfSize;
};
