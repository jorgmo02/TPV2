#pragma once
#include "Component.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"

class Gun : public Component {

public:
	Gun();
	Gun(double bulletSpeed, SDL_Keycode shootKey, int timeBetweenShots);
	~Gun();

	void init() override;
	void update() override;

private:
	double bulletSpeed_;
	SDL_Keycode shootKey_;
	int lastShootInstant_;
	int timeBetweenShots_;
	Transform* tr_;
};