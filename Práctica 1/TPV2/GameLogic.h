#pragma once

#include "AsteroidPool.h"
#include "BulletsPool.h"
#include "Collisions.h"
#include "Component.h"
#include "Entity.h"
#include "Health.h"
#include "Resources.h"
#include "ScoreManager.h"
#include "Transform.h"

class GameLogic: public Component {
public:
	GameLogic(Transform* cazaTR, AsteroidPool* aPool,
		BulletsPool* bPool, Health* health);
	virtual ~GameLogic();
	void init() override;
	void update() override;
	void checkWithFighter(Asteroid* a);
	void checkWithBullets(Asteroid* a);
private:
	void reset();
	Transform* cazaTR_;
	AsteroidPool* aPool_;
	BulletsPool* bPool_;
	Health* health_;
	ScoreManager *scoreManager_;
};

