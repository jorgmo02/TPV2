#pragma once

#include "System.h"

class FoodSystem: public System {
public:
	FoodSystem();
	void init() override;
	void update() override;

	void addFood(std::size_t n);
	void onEat(Entity *e);
	void disableAll();
private:
	int numOfFoodPieces_;

};

