#include "AsteroidPool.h"

AsteroidPool::AsteroidPool() :
	Component(ecs::AsteroidPool),
	pool_(&Asteroid::inUse),
	asteroidsInUse_(0) {
}

AsteroidPool::~AsteroidPool()
{
}

void AsteroidPool::generateAsteroids(int n) {

	vector<Asteroid*> p = pool_.getPool();

	for (int i = 0; i < n; i++) {
		generateRandomAsteroid(p[i]);
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

	Vector2D r((rand() % 100) - 50, (rand() % 100) - 50);	// margen con respecto al centro de la pantalla
	Vector2D pos(rand() % w, rand() % h);					// posición inicial del nuevo asteroide
	Vector2D target((Vector2D(w, h) / 2) + r);				// posición hacia la que se dirige el nuevo asteroide
	int m = (rand() % 9) + 1;								// número para multiplicar por el vector de velocidad
	int gen = (rand() % 2) + 1;								// generación del nuevo asteroide

	// aplica las modificaciones al asteroide
	a->set(pos, (target - pos).normalize() * (m / 10.0), rand() % 359, gen);
	
	asteroidsInUse_++;
}

void AsteroidPool::onCollision(Asteroid* a, Bullet* b) {
	// collision detection
	if (a->getGen() > 1) {
		a->setInUse(false);
		
		//pool_.getObj()->set();
		asteroidsInUse_++;
	}
}
