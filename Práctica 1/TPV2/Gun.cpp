#include "Gun.h"
#include <iostream>

Gun::Gun() :
	Gun(2, SDLK_SPACE, 250) {
}

Gun::Gun(double bulletSpeed, SDL_Keycode shootKey, int timeBetweenShots) :
	Component(ecs::Gun),
	tr_(nullptr),
	bulletSpeed_(bulletSpeed),
	shootKey_(shootKey),
	timeBetweenShots_(timeBetweenShots),
	lastShootInstant_(0)
{
}

Gun::~Gun()
{
}

void Gun::init() {
	tr_ = GETCMP1_(Transform);
	//pool_ = GETCMP1_(BulletsPool);
}

void Gun::update()
{
	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent() && SDL_GetTicks() - lastShootInstant_ >= timeBetweenShots_) {

		if (ih->isKeyDown(shootKey_)) {
			pool_->shoot(
				tr_->getPos(), tr_->getVel(),
				tr_->getW(), tr_->getH()
			);
			lastShootInstant_ = SDL_GetTicks();
		}
	}
}

