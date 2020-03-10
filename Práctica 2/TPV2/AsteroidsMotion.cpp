#include "AsteroidsMotion.h"

AsteroidsMotion::AsteroidsMotion() :
	Component(ecs::AsteroidsMotion)
{
}

AsteroidsMotion::~AsteroidsMotion()
{
}

void AsteroidsMotion::init() {
	AsteroidPool* asteroidPool_ = GETCMP1_(AsteroidPool);
	pool_ = asteroidPool_->getPool();
}

void AsteroidsMotion::update() {
	for (Asteroid* o : pool_) {
		if (o->inUse()) {
			o->setPos(o->getPos() + o->getVel());
			o->setRot(o->getRot() + 5);
			Vector2D oPos = o->getPos();

			if (oPos.getY() > game_->getWindowHeight())
				o->setPos(Vector2D(o->getPos().getX(), 0));
			else if (oPos.getY() < 0)
				o->setPos(Vector2D(o->getPos().getX(), game_->getWindowHeight()));

			if (oPos.getX() > game_->getWindowWidth())
				o->setPos(Vector2D(0, o->getPos().getY()));
			else if (oPos.getX() < 0)
				o->setPos(Vector2D(game_->getWindowWidth(), o->getPos().getY()));
		}
	}
}