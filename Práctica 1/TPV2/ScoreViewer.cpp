#include "ScoreViewer.h"

#include "Texture.h"
#include "Entity.h"
#include "SDL_macros.h"

ScoreViewer::ScoreViewer() :
		Component(ecs::ScoreViewer), //
		scoreManager_(nullptr) {
}

ScoreViewer::~ScoreViewer() {
}

void ScoreViewer::init() {
	scoreManager_ = GETCMP1_(ScoreManager);
}

void ScoreViewer::draw() {

	Texture score(game_->getRenderer(),
			to_string(scoreManager_->getScore()),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x111122ff) });
	score.render(
			game_->getWindowWidth() / 2 - score.getWidth() / 2, 10);


	if (scoreManager_->isGameOver())
	{
		string gameOverText = "";
		(!scoreManager_->hasWon()) ?
			gameOverText = "Game Over! You lost!" :
			gameOverText = "Game Over! You won!";

		Texture score(game_->getRenderer(),
			gameOverText,
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x111122ff) });
		score.render(
			game_->getWindowWidth() / 2 - score.getWidth() / 2, 100);
	}
}
