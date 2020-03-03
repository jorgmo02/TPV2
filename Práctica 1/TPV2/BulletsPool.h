#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "Asteroid.h"

class BulletsPool : public Component {
public:
	BulletsPool();
	BulletsPool(double bulletSpeed);
	virtual ~BulletsPool();

	void shoot(Vector2D pos, Vector2D vel, double w, double h, double rot);

	const vector<Bullet*>& getPool() {
		return pool_.getPool();
	};

	void onCollision(Asteroid* a, Bullet* b);

	void disableAll();

private:
	double bulletSpeed_;
	ObjectPool<Bullet, 10> pool_;

};