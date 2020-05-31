#include "RenderSystem.h"

#include "ecs.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "SDL_macros.h"
#include "SDLGame.h"

#include "Image.h"
#include "Transform.h"
#include "Texture.h"

RenderSystem::RenderSystem() :
	System(ecs::_sys_Render) {
}

void RenderSystem::update() {
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
		drawImage(e); // auto cast from unique_ptr to Entity*
	}

	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullets))
		drawImage(e); // auto cast from unique_ptr to Entity*

	drawCtrlMessages();
	drawScore();
	drawNames();
}

void RenderSystem::drawImage(Entity* e) {
	Transform* tr = e->getComponent<Transform>(ecs::Transform);
	Texture* tex = e->getComponent<Image>(ecs::Image)->tex_;

	SDL_Rect dest =
		RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
			tr->height_);
	tex->render(dest, tr->rotation_);
}

void RenderSystem::drawCtrlMessages() {
	GameCtrlSystem* gameCtrlSystem = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	if (!gameCtrlSystem->ready()) {
		Texture* msgTex = game_->getTextureMngr()->getTexture(
			Resources::WaitingForPlayer);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}
	else
	{
		GameCtrlSystem::State gameState = gameCtrlSystem->getState();
		if (gameState != GameCtrlSystem::RUNNING) {
			Texture* msgTex = game_->getTextureMngr()->getTexture(
				Resources::PressEnter);
			msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - msgTex->getHeight() - 10));
		}

		if (gameState == GameCtrlSystem::GAMEOVER) {
			Resources::TextureId msgTexTexture = Resources::GameOver;
			if (gameCtrlSystem->getScore(0) == gameCtrlSystem->getScore(1)) msgTexTexture = Resources::Draw;
			else msgTexTexture = (gameCtrlSystem->getScore(mngr_->getClientId()) == 3) ? Resources::YouWin : Resources::YouLose;

			Texture* msgTex = game_->getTextureMngr()->getTexture(msgTexTexture);
			msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - msgTex->getHeight()) / 2);
		}
	}
}

void RenderSystem::drawScore() {
	GameCtrlSystem* gameCtrl = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	Texture scoreTex(game_->getRenderer(),
		to_string(gameCtrl->getScore(0)) + " - "
		+ to_string(gameCtrl->getScore(1)),
		game_->getFontMngr()->getFont(Resources::ARIAL24),
		{ COLOR(0x111122ff) });
	scoreTex.render(game_->getWindowWidth() / 2 - scoreTex.getWidth() / 2, 10);
}

void RenderSystem::drawNames() {
	string thisName = mngr_->getClientName();
	string otherName = mngr_->getOtherName();

	Texture thisNameTexture(game_->getRenderer(), thisName, game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0x111122ff) });
	Texture otherNameTexture(game_->getRenderer(), otherName, game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0x111122ff) });

	int id = mngr_->getClientId();
	int posX = 14;
	// dibuja rectangulo blanco
	if (thisName != "          ") {
		SDL_Rect dest{
			(id * posX + 1) * game_->getWindowWidth() / 20,
			game_->getWindowHeight() / 20,
			thisNameTexture.getWidth(),
			thisNameTexture.getHeight()
		};
		SDL_SetRenderDrawColor(game_->getRenderer(), 255, 255, 255, 255);
		SDL_RenderFillRect(game_->getRenderer(), &dest);
	}

	thisNameTexture.render((id * posX + 1) * game_->getWindowWidth() / 20, game_->getWindowHeight() / 20);
	otherNameTexture.render(((1 - id) * posX + 1) * game_->getWindowWidth() / 20, game_->getWindowHeight() / 20);
}