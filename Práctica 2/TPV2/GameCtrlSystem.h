#pragma once

#include "ecs.h"
#include "System.h"
#include "Score.h"
#include "AsteroidsSystem.h"
#include "Score.h"
#include "GameState.h"

class GameCtrlSystem: public System {

public:

	void onFighterDeath() {
		gameState_->currentState_ = GameState::State::Stopped;
	};

	void onAsteroidsExtinction() {
		
	};

	GameState* getGameState() const {
		return gameState_;
	};

	void init() override {
		Entity *e = mngr_->addEntity();
		auto sc = e->addComponent<Score>();
		gameState_ = e->addComponent<GameState>();
		sc->points_ = 0;
		mngr_->setHandler<_hdlr_GameState>(e);

		game_->getAudioMngr()->playMusic(Resources::MainTheme, -1);
		game_->getAudioMngr()->pauseMusic();
	}

	void update() override {
		
		if (gameState_->currentState_ == GameState::State::Stopped) {
			auto ih = game_->getInputHandler();

			if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
				mngr_->getSystem<AsteroidsSystem>()->addAsteroids(10);
				gameState_->currentState_ = GameState::State::Started;
				game_->getAudioMngr()->resumeMusic();
			}
		}
	}

private:
	GameState* gameState_;
};

