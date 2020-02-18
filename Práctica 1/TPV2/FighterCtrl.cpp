#include "FighterCtrl.h"

FighterCtrl::FighterCtrl() :
	FighterCtrl(SDLK_UP, SDLK_LEFT, SDLK_RIGHT) {
}

FighterCtrl::FighterCtrl(SDL_Keycode forward, SDL_Keycode left,
	SDL_Keycode right) :
	Component(ecs::FighterCtrl),
	thrust_(5),
	speedLimit_(2) {
	setCtrlKeys(forward, left, right);
}

FighterCtrl::~FighterCtrl() {
}

void FighterCtrl::init() {
	tr_ = GETCMP1_(Transform);
}

void FighterCtrl::update() {
	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {

		if (ih->isKeyDown(forward_)) {

			Vector2D newVel = tr_->getVel() + Vector2D(0, -1).rotate(tr_->getRot()) * thrust_;

			if (newVel.magnitude() > speedLimit_)
				newVel = newVel.normalize() * speedLimit_;
			
			tr_->setVel(newVel);
		}
		else if (ih->isKeyDown(left_)) {
			tr_->setRot(tr_->getRot() - 5);
		}
		else if (ih->isKeyDown(right_)) {
			tr_->setRot(tr_->getRot() + 5);
		}
	}
}