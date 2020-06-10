#include "SoundSystem.h"
#include "SDLGame.h"

SoundSystem::SoundSystem() :
	System(ecs::_sys_Sound), //
	audioMngr_(nullptr) {
}

void SoundSystem::init() {
	audioMngr_ = game_->getAudioMngr();
	audioMngr_->playMusic(Resources::PacMan_Intro);
}

void SoundSystem::recieve(const msg::Message& msg)
{
	switch (msg.id) {
	case msg::_PACMAN_DEAD:
		audioMngr_->haltMusic();
		audioMngr_->playChannel(Resources::PacMan_Death, 0);
		break;
	case msg::_NO_MORE_TSUKKIS:
		audioMngr_->haltMusic();
		audioMngr_->playChannel(Resources::PacMan_Won, 0);
		break;
	case msg::_PACMAN_TSUKKI_COLLISION:
		audioMngr_->playChannel(Resources::PacMan_Eat, 0);
		break;
	default:
		break;
	}
}