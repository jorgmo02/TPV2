#include "BulletsPool.h"

BulletsPool::BulletsPool() :
	Component(ecs::BulletsPool),
	pool_([](Bullet* b) { return b->inUse(); }) {
}

BulletsPool::~BulletsPool()
{
}

void BulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h) {
	
}
