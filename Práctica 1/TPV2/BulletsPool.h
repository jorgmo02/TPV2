#pragma once
#include "Component.h"
#include "Entity.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "Asteroid.h"

class BulletsPool : public Component {
public:
	BulletsPool();
	~BulletsPool();
	void shoot(Vector2D pos, Vector2D vel, double w, double h);

	const vector<Bullet*>& getPool() {
		return pool_.getPool();
	};

	void onCollision(Asteroid* a, Bullet* b);

	void disableAll();

private:
	ObjectPool<Bullet, 10> pool_;

};

