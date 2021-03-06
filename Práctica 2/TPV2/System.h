#pragma once

class SDLGame;
class Manager;
#include "ecs.h"
#include "messages.h"

class System {
public:
	System() :
		mngr_(nullptr), game_(nullptr) {
	}

	virtual ~System() {
	}

	void setGame(SDLGame* game) {
		game_ = game;
	}

	void setMngr(Manager* mngr) {
		mngr_ = mngr;
	}

	virtual void init() {};
	virtual void update() {};

	virtual void recieve(const msg::Message& msg) {}

protected:
	Manager* mngr_;
	SDLGame* game_;

};