#include "BulletsMotion.h"

BulletsMotion::BulletsMotion() :
	Component(ecs::BulletsMotion) {
}

BulletsMotion::~BulletsMotion()
{
}

void BulletsMotion::init()
{
	BulletsPool* bulletsPool = GETCMP1_(BulletsPool);
	pool_ = bulletsPool->getPool();
}

void BulletsMotion::update()
{
	for (auto o : pool_) {
		if(o->inUse())
			o->setPos(o->getPos() + o->getVel());
	}
}
