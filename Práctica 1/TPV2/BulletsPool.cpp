#include "BulletsPool.h"

BulletsPool::BulletsPool() :
	Component(ecs::BulletsPool),
	pool_([](Bullet* b) { return b->inUse(); }) {
}

BulletsPool::~BulletsPool()
{
}
