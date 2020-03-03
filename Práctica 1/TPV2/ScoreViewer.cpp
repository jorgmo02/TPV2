#include "ScoreViewer.h"

#include "Texture.h"
#include "Entity.h"
#include "SDL_macros.h"

ScoreViewer::ScoreViewer() :
	ScoreViewer(0x111122ff) {
}

ScoreViewer::ScoreViewer(int scoreViewerColor) :
	Component(ecs::ScoreViewer), //
	scoreManager_(nullptr),
	scoreViewerColor_(scoreViewerColor) {
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
		{ COLOR(scoreViewerColor_) });
	score.render(
		game_->getWindowWidth() / 2 - score.getWidth() / 2, 10);

	if (scoreManager_->isGameOver())
	{
		string gameOverText;
		(scoreManager_->isWin()) ?
			gameOverText = "Game Over! You won!" :
			gameOverText = "Game Over! You lost!";

		Texture gameOverImg(game_->getRenderer(),
			gameOverText,
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(scoreViewerColor_) });
		gameOverImg.render(
			game_->getWindowWidth() / 2 - gameOverImg.getWidth() / 2, 100);
	}
}
