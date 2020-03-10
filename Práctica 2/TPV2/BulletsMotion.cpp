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
		if (o->inUse()) {
			o->setPos(o->getPos() + o->getVel());

			Vector2D oPos = o->getPos();

			if (oPos.getY() > game_->getWindowHeight() ||
				oPos.getY() < 0 ||
				oPos.getX() > game_->getWindowWidth() ||
				oPos.getX() < 0)
				o->setInUse(false);
		}
	}
}
