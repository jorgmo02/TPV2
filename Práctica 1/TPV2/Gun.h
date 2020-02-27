#pragma once
#include "Component.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"
#include "BulletsPool.h"

class Gun : public Component {

public:
	Gun(BulletsPool* p);
	Gun(BulletsPool* p, double bulletSpeed, SDL_Keycode shootKey, int timeBetweenShots);
	virtual ~Gun();

	void init() override;
	void update() override;

private:
	double bulletSpeed_;
	SDL_Keycode shootKey_;
	int lastShootInstant_;
	int timeBetweenShots_;
	Transform* tr_;
	BulletsPool* pool_;
};