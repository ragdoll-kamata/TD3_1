#pragma once

#include "Sphere.h"
#include "AABB.h"
namespace CollisionDetection
{
	bool IsCollision(Sphere s1, Sphere s2);

	bool IsCollision(AABB aabb1, AABB aabb2);

	bool IsCollision(Sphere s, AABB aabb);
	bool IsCollision(AABB aabb, Sphere s);

	bool IsCollision(Sphere s, KamataEngine::Vector3 v);
    bool IsCollision(KamataEngine::Vector3 v, Sphere s);

	bool IsCollision(AABB aabb, KamataEngine::Vector3 v);
    bool IsCollision(KamataEngine::Vector3 v, AABB aabb);

};

