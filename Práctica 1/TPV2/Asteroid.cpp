#include "Asteroid.h"

Asteroid::Asteroid() :  Asteroid(
	Vector2D(0, 0),		// pos
	Vector2D(1, 1),	// vel
	0,					// rot
	3					// gen
) {
}

Asteroid::Asteroid(Vector2D pos, Vector2D vel, double rot, int gen) :
	baseTam_(10),
	baseRate_(3.0),
	pos_(pos),
	vel_(vel),
	w_(baseTam_ + gen * baseRate_),
	h_(baseTam_ + gen * baseRate_),
	rot_(rot),
	gen_(gen),
	inUse_(false) {
}

void Asteroid::set(Vector2D pos, Vector2D vel, double rot, int gen) {
	pos_ = pos;
	vel_ = vel;
	rot_ = rot;
	gen_ = gen;
	inUse_ = true;
	updateScale();
}

Asteroid::~Asteroid()
{
}

void Asteroid::updateScale() {
	w_ = baseTam_ + gen_ * baseRate_;
	h_ = baseTam_ + gen_ * baseRate_;
}