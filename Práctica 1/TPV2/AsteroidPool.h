#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Asteroid.h"
class Bullet; // sustituir por include bullet

class AsteroidPool : public Component {

private:
	ObjectPool<Asteroid, 30> pool_;
	int asteroidsInUse_;
	void generateRandomAsteroid(Asteroid* a);

public:
	AsteroidPool();
	virtual ~AsteroidPool();

	void generateAsteroids(int n);
	void disableAll();
	void onCollision(Asteroid* a, Bullet* b);

	int getNumOfAsteroid() {
		return asteroidsInUse_;
	};

	vector<Asteroid*> getPool() {
		return pool_.getPool();
	}
};

