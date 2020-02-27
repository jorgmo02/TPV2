#pragma once
#include "Component.h"
#include "Texture.h"
#include "SDL_macros.h"

class Health : public Component {
private:
	int health_ = 3;
	Texture* heart_ = nullptr;
public:
	Health();
	virtual ~Health();

	void init() override;
	void draw() override;
	void substractLife();
};

