#include "Asteroid.h"

Asteroid::Asteroid() :  Asteroid(
	Vector2D(0, 0),		// pos
	Vector2D(1, 1),	// vel
	50,					// w
	50,					// h
	0,					// rot
	3					// gen
) {
}

Asteroid::Asteroid(Vector2D pos, Vector2D vel, int w, int h, double rot, int gen) :
	pos_(pos),
	vel_(vel),
	w_(w),
	h_(h),
	rot_(rot),
	gen_(gen) {
}

Asteroid::~Asteroid()
{
}
