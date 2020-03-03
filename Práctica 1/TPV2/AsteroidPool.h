#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Asteroid.h"
#include "Bullet.h"

class AsteroidPool : public Component {

private:
	ObjectPool<Asteroid, 30> pool_;
	int asteroidsInUse_;
	int asteroidsVel_;

	void generateRandomAsteroid(Asteroid* a);

	void generateAsteroid(Asteroid* newAst, Vector2D aPos, Vector2D aVel, int gen);

public:
	AsteroidPool();
	AsteroidPool(int asteroidsVel);
	virtual ~AsteroidPool();

	void generateAsteroids(int n);
	void disableAll();
	void onCollision(Asteroid* a, Bullet* b);

	const vector<Asteroid*>& getPool() {
		return pool_.getPool();
	}

	inline int getNumOfAsteroid() const {
		return asteroidsInUse_;
	};
};