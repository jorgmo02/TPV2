#pragma once

#include "System.h"
#include <SDL.h>

class GhostsSystem: public System {
public:
	GhostsSystem();
	void init() override;
	virtual void recieve(const msg::Message& msg) override;
	void update() override;

private:
	void onCollisionWithPacMan(Entity *e);
	void addGhosts(std::size_t n);
	void disableAll();

	Uint32 lastTimeAdded_;
	int maxGhosts_;
	int numOfGhosts_;
};

