#include "AsteroidPool.h"

AsteroidPool::AsteroidPool() :
	Component(ecs::AsteroidPool),
	pool_([](Asteroid* a) { return a->inUse(); }),
	asteroidsInUse_(0) {
}

AsteroidPool::~AsteroidPool()
{
}

void AsteroidPool::generateAsteroids(int n) {

	for (int i = 0; i < n; i++) {
		Asteroid* o = pool_.getObj();
		if(o != nullptr)
			generateRandomAsteroid(o);
	}
}

void AsteroidPool::disableAll() {

	for (Asteroid* a : pool_.getPool()) {
		a->setInUse(false);
	}
	asteroidsInUse_ = 0;
}

void AsteroidPool::generateRandomAsteroid(Asteroid* a) {

	int h = game_->getWindowHeight();
	int w = game_->getWindowWidth();

	RandomNumberGenerator* random = game_->getRandGen();

	Vector2D r((random->nextInt() % 100) - 50, (random->nextInt() % 100) - 50);	// margen con respecto al centro de la pantalla
	Vector2D pos(random->nextInt() % w, random->nextInt() % h);					// posición inicial del nuevo asteroide
	Vector2D target((Vector2D(w, h) / 2) + r);				// posición hacia la que se dirige el nuevo asteroide
	int m = (random->nextInt() % 10) + 1;								// número para multiplicar por el vector de velocidad
	int gen = (random->nextInt() % 3) + 1;								// generación del nuevo asteroide

	// aplica las modificaciones al asteroide y hace setInUse(true)
	a->set(pos, (target - pos).normalize() * (m / 10.0), random->nextInt() % 359, gen);
	
	asteroidsInUse_++;
}

void AsteroidPool::onCollision(Asteroid* a, Bullet* b) {
	// collision detection
	a->setInUse(false);
	if (a->getGen() > 1) {
		
		//pool_.getObj()->set();
		asteroidsInUse_++;
	}
}