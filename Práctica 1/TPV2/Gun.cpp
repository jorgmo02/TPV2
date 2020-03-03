#include "Gun.h"

Gun::Gun(BulletsPool* p) :
	Gun(p, SDLK_SPACE, 250) {
}

Gun::Gun(BulletsPool* p, SDL_Keycode shootKey, int timeBetweenShots) :
	Component(ecs::Gun),
	pool_(p),
	tr_(nullptr),
	shootKey_(shootKey),
	timeBetweenShots_(timeBetweenShots),
	lastShootInstant_(0) {
}

Gun::~Gun()
{
}

void Gun::init() {
	tr_ = GETCMP1_(Transform);
}

void Gun::update()
{
	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent() && SDL_GetTicks() - lastShootInstant_ >= timeBetweenShots_) {

		if (ih->isKeyDown(shootKey_)) {
			pool_->shoot(
				tr_->getPos(), tr_->getVel(),
				tr_->getW(), tr_->getH(),
				tr_->getRot()
			);
			game_->getAudioMngr()->playChannel(Resources::Wall_Hit, 0);
			lastShootInstant_ = SDL_GetTicks();
		}
	}
}

