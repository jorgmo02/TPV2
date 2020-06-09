#pragma once

#include "System.h"
#include "Transform.h"
#include "Entity.h"

class PacManSystem: public System {
public:
	PacManSystem();
	void init() override;
	void update() override;

	// TODO: these methods should go private
	void resetPacManPosition();
private:
	Entity *pacman_;
	Transform *tr_;
};

