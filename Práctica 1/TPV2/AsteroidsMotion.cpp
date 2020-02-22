#include "AsteroidsMotion.h"

AsteroidsMotion::AsteroidsMotion() :
	Component(ecs::AsteroidsMotion),
	asteroidPool_(nullptr)
{
}

AsteroidsMotion::~AsteroidsMotion()
{
}

void AsteroidsMotion::init() {
	asteroidPool_ = GETCMP1_(AsteroidPool);
}
