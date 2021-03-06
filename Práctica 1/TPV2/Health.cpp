#include "Health.h"

Health::Health() :
	Health(3) {
}

Health::Health(int lifes) :
	Component(ecs::Health),
	maxHealth_(lifes),
	health_(lifes) {
}

Health::~Health() {

}

void Health::init() {
	heart_ = game_->getTextureMngr()->getTexture(Resources::Heart);
}

void Health::draw() {
	int wWidth = game_->getWindowWidth();
	int wHeight = game_->getWindowHeight();
	
	SDL_Rect rect
		RECT(wWidth / 20, wHeight / 20, wWidth / 20, wHeight / 20);

	for (int i = 0; i < health_; i++) {
		heart_->render(rect);
		rect.x += wWidth / 18;
 	}
}

void Health::substractLife() {
	health_--;
}