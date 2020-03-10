#include "Bullet.h"

Bullet::Bullet() : Bullet (
	Vector2D(0, 0),		// pos
	Vector2D(1, 1),		// vel
	0					// rot
) {
}

Bullet::Bullet(Vector2D pos, Vector2D vel, double rot) :
	pos_(pos),
	vel_(vel),
	h_(10),
	w_(10),
	rot_(rot),
	inUse_(false) {
}

void Bullet::set(Vector2D pos, Vector2D vel, double rot) {
	pos_ = pos;
	vel_ = vel;
	rot_ = rot;
	inUse_ = true;
}

Bullet::~Bullet()
{
}