#include "AsteroidsViewer.h"

AsteroidsViewer::AsteroidsViewer() :
	AsteroidsViewer(47, 90, 207, 250) {
}

AsteroidsViewer::AsteroidsViewer(int x, int y, int w, int h) :
	Component(ecs::AsteroidsViewer),
	texture_(nullptr) {
	clip = RECT(x, y, w, h);
}

AsteroidsViewer::~AsteroidsViewer() {
}

void AsteroidsViewer::init() {

	texture_ = game_->getTextureMngr()->getTexture(Resources::Asteroid);
}

void AsteroidsViewer::draw() {
	SDL_Rect rect;

	for (auto o : pool_)
		if (o->inUse()) {
			rect = RECT(o->getPos().getX(), o->getPos().getY(), o->getWidth(), o->getHeight());
			texture_->render(rect, o->getRot(), clip);
		}
}