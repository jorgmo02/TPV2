#include "AsteroidsViewer.h"

AsteroidsViewer::AsteroidsViewer() :
	Component(ecs::AsteroidsViewer),
	texture_(nullptr) {
}

AsteroidsViewer::~AsteroidsViewer() {
}

void AsteroidsViewer::init() {
	AsteroidPool* asteroidPool_ = GETCMP1_(AsteroidPool);
	pool_ = asteroidPool_->getPool();
	texture_ = game_->getTextureMngr()->getTexture(Resources::Asteroid);
}

void AsteroidsViewer::draw() {
	SDL_Rect rect;
	for (auto o : pool_)
		if (o->inUse()) {
			rect = RECT(o->getPos().getX(), o->getPos().getY(), o->getWidth(), o->getHeight());
			texture_->render(rect, o->getRot());
		}
}