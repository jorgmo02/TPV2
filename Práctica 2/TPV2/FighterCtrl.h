#pragma once
#include "Component.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"

class FighterCtrl : public Component
{
public:
	FighterCtrl();
	FighterCtrl(SDL_Keycode forward, SDL_Keycode left, SDL_Keycode right,
		double thrust, double speedLimit);
	virtual ~FighterCtrl();

	inline void setCtrlKeys(SDL_Keycode forward, SDL_Keycode left,
		SDL_Keycode right) {
		forward_ = forward;
		left_ = left;
		right_ = right;
	}

	void init() override;
	void update() override;

private:
	SDL_Keycode forward_;
	SDL_Keycode left_;
	SDL_Keycode right_;
	Transform* tr_;
	double thrust_;
	double speedLimit_;
};

