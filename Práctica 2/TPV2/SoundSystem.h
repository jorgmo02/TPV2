#pragma once

#include "SDLGame.h"
#include "System.h"
#include "Manager.h"

class SoundSystem : public System {
public:
	SoundSystem() {
	}

	void init() override {
		audioManager_ = game_->getAudioMngr();
	}

	virtual void recieve(const msg::Message& msg) override {
		switch (msg.id) {
		case msg::_BULLET_ASTEROID_COLLISION_:
			audioManager_->playChannel(Resources::Paddle_Hit, 0);
			break;
		case msg::_FIGHTER_ASTEROID_COLLISION_:
			audioManager_->playChannel(Resources::Explosion, 0);
			break;
		case msg::_SHOOT_:
			audioManager_->playChannel(Resources::Wall_Hit, 0);
			break;
		case msg::_DISABLE_ALL_:
			audioManager_->pauseMusic();
			break;
		case msg::_NEW_TRY_:
			audioManager_->playMusic(Resources::MainTheme, -1);
			audioManager_->resumeMusic();
			break;
		default:
			break;
		}
	}

private:
	AudioManager* audioManager_;
};

