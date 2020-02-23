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
	for (Asteroid* a : pool_) {
		
	}
}
