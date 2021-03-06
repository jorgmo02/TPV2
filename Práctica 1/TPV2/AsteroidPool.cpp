#include "AsteroidPool.h"

AsteroidPool::AsteroidPool() :
	AsteroidPool(10) {
}

AsteroidPool::AsteroidPool(int asteroidsVel) :
	Component(ecs::AsteroidPool),
	pool_([](Asteroid* a) { return a->inUse(); }),
	asteroidsInUse_(0),
	asteroidsVel_(asteroidsVel) {
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
	Vector2D pos(random->nextInt() % w, random->nextInt() % h);					// posici�n inicial del nuevo asteroide
	Vector2D target((Vector2D(w, h) / 2) + r);									// posici�n hacia la que se dirige el nuevo asteroide
	double m = (random->nextInt() % asteroidsVel_) + 1;					// n�mero para multiplicar por el vector de velocidad
	int gen = (random->nextInt() % 3) + 1;										// generaci�n del nuevo asteroide

	// aplica las modificaciones al asteroide y hace setInUse(true)
	a->set(pos, (target - pos).normalize() * (m / 10.0), random->nextInt() % 359, gen);
	
	asteroidsInUse_++;
}

void AsteroidPool::generateAsteroid(Asteroid* newAst, Vector2D aPos, Vector2D aVel, int gen) {

	Vector2D vel(aVel.getY(), aVel.getX());
	Vector2D pos = aPos + vel * vel.magnitude();					// posici�n inicial del nuevo asteroide

	// aplica las modificaciones al asteroide y hace setInUse(true)
	newAst->set(pos, vel, game_->getRandGen()->nextInt() % 359, gen);

	asteroidsInUse_++;
}

void AsteroidPool::onCollision(Asteroid* a, Bullet* b) {
	if (a->getGen() > 1) {
		generateAsteroid(pool_.getObj(), a->getPos(), a->getVel(), a->getGen() - 1);
		generateAsteroid(pool_.getObj(), a->getPos(), a->getVel() * -1, a->getGen() - 1);
	}
	a->setInUse(false);
	asteroidsInUse_--;
}