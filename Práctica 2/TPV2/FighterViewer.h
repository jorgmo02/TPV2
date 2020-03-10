#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"
#include "Texture.h"

class FighterViewer : public Component {
public:
	FighterViewer();
	FighterViewer(int x, int y, int w, int h);
	virtual ~FighterViewer();
	void init() override;
	void draw() override;

private:
	Transform* tr_;
	SDL_Rect clip;
	Texture* texture_;
};