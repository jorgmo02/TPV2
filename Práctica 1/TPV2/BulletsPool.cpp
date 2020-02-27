#include "BulletsPool.h"
#include "Entity.h"

BulletsPool::BulletsPool() :
	Component(ecs::BulletsPool),
	pool_([](Bullet* b) { return b->inUse(); }) {
}

BulletsPool::~BulletsPool()
{
}

void BulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h) {
	Bullet* b = pool_.getObj();

	double rot = Vector2D(0, -1).angle(vel);
	Vector2D bulletPos = pos + Vector2D(w / 2, h / 2) + Vector2D(0, -(h / 2 + 5.0)).rotate(rot);
	Vector2D bulletVel = Vector2D(0, -1).rotate(rot) * 2;				// posición inicial del nuevo asteroide

	// aplica las modificaciones y hace setInUse(true)
	b->set(pos, vel, rot);
}

void BulletsPool::onCollision(Asteroid* a, Bullet* b) {
	b->setInUse(false);
}

void BulletsPool::disableAll() {
	for (auto o : pool_.getPool()) {
		o->setInUse(false);
	}
}
