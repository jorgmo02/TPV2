#pragma once

#include "System.h"
#include <SDL.h>

class GhostsSystem: public System {
public:
	GhostsSystem();
	void init() override;
	void update() override;

	// TODO: these methods should go private
	void onCollisionWithPacMan(Entity *e);
	void addGhosts(std::size_t n);
	void disableAll();
private:
	Uint32 lastTimeAdded_;
	int maxGhosts_;
	int numOfGhosts_;

};

