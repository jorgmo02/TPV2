#pragma once

#include "ecs.h"
#include "SDLGame.h"
#include "SDL_macros.h"
#include "Manager.h"
#include "System.h"
#include "Entity.h"
#include "Score.h"
#include "Transform.h"
#include "ImageComponent.h"
#include "Texture.h"
#include "GameCtrlSystem.h"

class RenderSystem: public System {
public:

	void setFighterClip(SDL_Rect clip) {
		fighterClip_ = clip;
	}

	void draw(Entity *e) {
		Transform *tr = e->getComponent<Transform>();
		ImageComponent *img = e->getComponent<ImageComponent>();
		SDL_Rect dest =
		RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
				tr->height_);
		img->tex_->render(dest, tr->rotation_);
	}

	void draw(Entity* e, SDL_Rect clip) {
		Transform* tr = e->getComponent<Transform>();
		ImageComponent* img = e->getComponent<ImageComponent>();
		SDL_Rect dest =
			RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
				tr->height_);
		img->tex_->render(dest, tr->rotation_, clip);
	}

	void drawScore() {
		auto sc =
				mngr_->getHandler<_hdlr_GameState>()->getComponent<Score>();
		Texture scoreMsg(game_->getRenderer(), std::to_string(sc->points_),
				game_->getFontMngr()->getFont(Resources::ARIAL24),
				{ COLOR(0x0000ffff) });
		scoreMsg.render(game_->getWindowWidth() / 2 - scoreMsg.getWidth() / 2,
				10);

	}

	void drawHealth() {
		int playerHealth = mngr_->getHandler<_hdlr_Fighter>()->getComponent<Health>()->health_;

		int wWidth = game_->getWindowWidth();
		int wHeight = game_->getWindowHeight();

		SDL_Rect rect
			RECT(wWidth / 20, wHeight / 20, wWidth / 20, wHeight / 20);

		for (int i = 0; i < playerHealth; i++) {
			game_->getTextureMngr()->getTexture(Resources::Heart)->render(rect);
			rect.x += wWidth / 18;
		}
	}

	void update() override {

		GameState::State currentState = mngr_->getSystem<GameCtrlSystem>()->getGameState()->currentState_;

		if (currentState == GameState::State::Started) {

			// draw asteroids
			for (auto& e : mngr_->getGroupEntities<_grp_Asteroids>()) {
				draw(e);
			}
			// draw bullets
			for (auto& e : mngr_->getGroupEntities<_grp_Bullets>()) {
				draw(e);
			}
			// draw fighter
			draw(mngr_->getHandler<_hdlr_Fighter>(), fighterClip_);
		}
		else if (currentState == GameState::State::Stopped) {
			Texture msg(game_->getRenderer(), "Press ENTER to start", game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0xff0000ff) });
			// info message
			msg.render(game_->getWindowWidth() / 2 - msg.getWidth() / 2, game_->getWindowHeight() - msg.getHeight() - 10);
		}

		else {
			string winText;
			(currentState == GameState::State::Win) ? winText = "You win!" : winText = "You lose!";

			Texture winTexture(game_->getRenderer(), winText, game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0xff0000ff) });
			// win/lose message
			winTexture.render(game_->getWindowWidth() / 2 - winTexture.getWidth() / 2, winTexture.getHeight());

			Texture msg(game_->getRenderer(), "Press ENTER to start a new game", game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0xff0000ff) });
			// info message
			msg.render(game_->getWindowWidth() / 2 - msg.getWidth() / 2, game_->getWindowHeight() - msg.getHeight() - 10);
		}

		// draw score
		drawScore();
		drawHealth();
	}

private:
	SDL_Rect fighterClip_;
};

