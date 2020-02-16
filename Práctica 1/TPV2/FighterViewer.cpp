#include "FighterViewer.h"

FighterViewer::FighterViewer() :
	Component(ecs::FighterViewer), //
	tr_(nullptr) {
	texture_ = game_->getTextureMngr()->getTexture(Resources::Airplanes);
	clip = RECT(47, 90, 207, 250);
}

FighterViewer::FighterViewer(int x, int y, int w, int h) :
	Component(ecs::FighterViewer), //
	tr_(nullptr) {
	texture_ = game_->getTextureMngr()->getTexture(Resources::Airplanes);
	clip = RECT(x, y, w, h);
}

FighterViewer::~FighterViewer() {
}

void FighterViewer::init() {
	tr_ = GETCMP1_(Transform);
}

void FighterViewer::draw() {

	SDL_Rect rect
		RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(),
			tr_->getH());

	texture_->render(rect, clip);
}