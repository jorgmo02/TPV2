#pragma once
#include "Component.h"
#include "Texture.h"

class Health : public Component {
private:
	int health_ = 0;
	Texture* heart_ = nullptr;
public:

};

