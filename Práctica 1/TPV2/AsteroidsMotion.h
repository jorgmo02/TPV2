#pragma once
#include "Component.h"
#include "AsteroidPool.h"
#include "Entity.h"

class AsteroidsMotion :	public Component {
public:
	AsteroidsMotion();
	~AsteroidsMotion();

	void init() override;

private:
	AsteroidPool* asteroidPool_;

};

