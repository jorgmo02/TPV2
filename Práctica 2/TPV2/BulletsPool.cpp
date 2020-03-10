#include "BulletsPool.h"

BulletsPool::BulletsPool() :
	BulletsPool(2.0) {
}

BulletsPool::BulletsPool(double bulletSpeed) :
	Component(ecs::BulletsPool),
	pool_([](Bullet* b) { return b->inUse(); }),
	bulletSpeed_(bulletSpeed) {
}

BulletsPool::~BulletsPool()
{
}

void BulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h, double rot) {
	Bullet* b = pool_.getObj();

	if (b != nullptr) {

		Vector2D bulletPos =
			pos +
			Vector2D(w / 2, h / 2) +
			Vector2D(0, -(h / 2)).rotate(rot);

		Vector2D bulletVel = Vector2D(0, -1).rotate(rot) * bulletSpeed_;				// posición inicial del nuevo asteroide

		// aplica las modificaciones y hace setInUse(true)
		b->set(bulletPos, bulletVel, rot);
	}
}

void BulletsPool::onCollision(Asteroid* a, Bullet* b) {
	b->setInUse(false);
}

void BulletsPool::disableAll() {
	for (auto o : pool_.getPool()) {
		o->setInUse(false);
	}
}
