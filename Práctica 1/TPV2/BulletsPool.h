#pragma once
#include "Component.h"
#include "Entity.h"
#include "ObjectPool.h"
#include "Bullet.h"

class BulletsPool : public Component {

public:
	BulletsPool();
	~BulletsPool();
	void shoot(Vector2D pos, Vector2D vel, double w, double h);

private:
	ObjectPool<Bullet, 10> pool_;

};

