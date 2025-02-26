#pragma once
#include "math/Vector3.h"

struct AABB final {
	KamataEngine::Vector3 min;
	KamataEngine::Vector3 max;
};
