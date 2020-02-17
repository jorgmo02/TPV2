#include "FighterCtrl.h"

FighterCtrl::FighterCtrl() :
	FighterCtrl(SDLK_UP, SDLK_LEFT, SDLK_RIGHT) {
}

FighterCtrl::FighterCtrl(SDL_Keycode forward, SDL_Keycode left,
	SDL_Keycode right) :
	Component(ecs::FighterCtrl) {
	setCtrlKeys(forward, left, right);
}

FighterCtrl::~FighterCtrl() {
}

void FighterCtrl::init() {
	tr_ = GETCMP1_(Transform);
}

void FighterCtrl::setFighterMotion(FighterMotion* fm) {
	fm_ = fm;
}

void FighterCtrl::update() {
	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(forward_)) {
			fm_->accelerate();
		}
		else if (ih->isKeyDown(left_)) {
			tr_->setRot(tr_->getRot() - 5);
		}
		else if (ih->isKeyDown(right_)) {
			tr_->setRot(tr_->getRot() + 5);
		}
	}
}