#include "AsteroidPool.h"

AsteroidPool::AsteroidPool() :
	Component(ecs::AsteroidPool),
	pool_(&Asteroid::inUse) {

}

AsteroidPool::~AsteroidPool()
{
}

void AsteroidPool::generateAsteroids(int n) {
	for (int i = 0; i < n; i++) {
		generateRandomAsteroid();
	}
}

void AsteroidPool::disableAll() {
	for (Asteroid* a : pool_.getPool()) {
		a->setInUse(false);
	}
}

void AsteroidPool::generateRandomAsteroid() {

	int h = game_->getWindowHeight();
	int w = game_->getWindowWidth();

	Vector2D r(rand() % 100 - 50, rand() % 100 - 50);

	Vector2D pos(rand() % w, rand() % h);

	Vector2D target((Vector2D(w, h) / 2) + r);

	int m = (rand() % 9) + 1;
	
	int gen = (rand() % 2) + 1;

	Asteroid* a = new Asteroid(pos, (target-pos).normalize() * (m / 10.0), rand() % 359, gen);
}
