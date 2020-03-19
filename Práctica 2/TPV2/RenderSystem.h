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

	void update() override {

		// draw asteroids
		for (auto &e : mngr_->getGroupEntities<_grp_Asteroids>()) {
			draw(e);
		}
		// draw bullets
		for (auto &e : mngr_->getGroupEntities<_grp_Bullets>()) {
			draw(e);
		}

		// draw fighter
		draw(mngr_->getHandler<_hdlr_Fighter>(), fighterClip_);

		// draw score
		drawScore();

		// info message
		Texture msg(game_->getRenderer(),"Press ENTER to add More Stars", game_->getFontMngr()->getFont(Resources::ARIAL24),{COLOR(0xff0000ff)});
		msg.render(game_->getWindowWidth()/2-msg.getWidth()/2,game_->getWindowHeight()-msg.getHeight()-10);
	}

private:
	SDL_Rect fighterClip_;
};

