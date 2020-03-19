#pragma once

#include "SDLGame.h"
#include "System.h"
#include "Manager.h"
#include "InputHandler.h"
#include "BulletsSystem.h"
#include "Transform.h"

class FighterGunSystem : public System {
public:
	FighterGunSystem() :
		tr_(nullptr) {
	}

	inline void setFighterGunConfig(int timeBetweenShots, SDL_Keycode shoot)
	{
		timeBetweenShots_ = timeBetweenShots;
		lastShootInstant_ = 0;
		shoot_ = shoot;
	}

	void init() override {
		tr_ = mngr_->getHandler<_hdlr_Fighter>()->getComponent<Transform>();
	}

	void update() override {
		auto ih = InputHandler::instance();
		assert(tr_ != nullptr);

		if (ih->keyDownEvent()) {
			 if (ih->isKeyDown(shoot_) && SDL_GetTicks() - lastShootInstant_ >= timeBetweenShots_) {
				mngr_->getSystem<BulletsSystem>()->shoot(
					tr_->position_, tr_->velocity_,
					tr_->width_, tr_->height_,
					tr_->rotation_
				);
				game_->getAudioMngr()->playChannel(Resources::Wall_Hit, 0);
				lastShootInstant_ = SDL_GetTicks();
			}
		}
	}

private:
	Transform* tr_;

	int lastShootInstant_;
	int timeBetweenShots_;

	SDL_Keycode shoot_;
};

