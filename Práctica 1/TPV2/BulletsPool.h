#pragma once
#include "Component.h"
#include "Entity.h"
#include "ObjectPool.h"
#include "Bullet.h"

class BulletsPool : public Component {

public:
	BulletsPool();
	~BulletsPool();

private:
	ObjectPool<Bullet, 10> pool_;

};

