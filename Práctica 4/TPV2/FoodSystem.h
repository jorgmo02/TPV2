#pragma once

#include "System.h"

class FoodSystem: public System {
public:
	FoodSystem();
	void init() override;
	virtual void recieve(const msg::Message& msg) override;
	void update() override;

private:
	void addFood(std::size_t n);
	void onEat(Entity *e);
	void disableAll();

	int numOfFoodPieces_;

};

