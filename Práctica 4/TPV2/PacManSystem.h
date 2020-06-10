#pragma once

#include "System.h"
#include "Transform.h"
#include "Entity.h"

class PacManSystem: public System {
public:
	PacManSystem();
	void init() override;
	virtual void recieve(const msg::Message& msg) override;
	void update() override;
	int lifes = 1;

private:
	void resetPacManPosition();

	Entity *pacman_;
	Transform *tr_;
};

