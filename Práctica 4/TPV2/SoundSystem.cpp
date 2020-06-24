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
	case msg::_GAME_OVER:
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
	case msg::_GAME_START:
		audioMngr_->haltMusic();
		break;
	case msg::_GAME_RESET:
		audioMngr_->haltMusic();
		audioMngr_->haltChannel();
		audioMngr_->playMusic(Resources::PacMan_Intro);
		break;
	default:
		break;
	}
}