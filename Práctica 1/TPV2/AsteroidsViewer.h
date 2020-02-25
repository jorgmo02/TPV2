#pragma once
#include "Component.h"
#include "AsteroidPool.h"
#include "SDL_macros.h"
#include "Entity.h"

class AsteroidsViewer : public Component {
public:
	AsteroidsViewer();
	virtual ~AsteroidsViewer();
	void init() override;
	void draw() override;

private:
	vector<Asteroid*> pool_;
	Texture* texture_;
};