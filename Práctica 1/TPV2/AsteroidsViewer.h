#pragma once
#include "Component.h"
#include "AsteroidPool.h"
#include "SDL_macros.h"
#include "Entity.h"

class AsteroidsViewer : public Component {
public:
	AsteroidsViewer();
	AsteroidsViewer(int x, int y, int w, int h);
	virtual ~AsteroidsViewer();
	void init() override;
	void draw() override;

private:
	vector<Asteroid*> pool_;
	SDL_Rect clip;
	Texture* texture_;
};