#pragma once
#include "Component.h"
#include "Texture.h"
#include "SDL_macros.h"

class Health : public Component {
private:
	int health_;
	int maxHealth_;	
	Texture* heart_ = nullptr;
public:
	Health();
	Health(int lifes);
	virtual ~Health();

	void init() override;
	void draw() override;
	void substractLife();
	inline void setLifes(int lifes) {
		health_ = lifes;
	}
	inline int getLifes() const {
		return health_;
	}

	inline int getMaxHealth() const {
		return maxHealth_;
	}

};

