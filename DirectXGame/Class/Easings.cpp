#include "Easings.h"


namespace Easings {

float EaseInQuad(float t) { return t * t; }

float EaseOutQuad(float t) { return 1.0f - EaseInQuad(1.0f - t); }

float EaseInQuart(float t) { return t * t * t * t; }

float EaseOutQuart(float t) { return 1.0f - EaseInQuart(1.0f - t); }

float EaseInBack(float t) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;

	return c3 * t * t * t - c1 * t * t;
}



} // namespace Easings