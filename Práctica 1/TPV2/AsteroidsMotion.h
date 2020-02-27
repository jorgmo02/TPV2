#pragma once
#include "Component.h"
#include "AsteroidPool.h"
#include "Entity.h"

class AsteroidsMotion :	public Component {
public:
	AsteroidsMotion();
	virtual ~AsteroidsMotion();

	void init() override;
	void update() override;

private:
	vector<Asteroid*> pool_;
};

