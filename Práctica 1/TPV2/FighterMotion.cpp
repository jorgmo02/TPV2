#include "FighterMotion.h"

FighterMotion::FighterMotion() :
	FighterMotion(0.995)
{
}

FighterMotion::FighterMotion(double reduceRate) :
	Component(ecs::FighterMotion),
	reduceRate_(reduceRate)
{
}

FighterMotion::~FighterMotion()
{
}

void FighterMotion::init() {
	tr_ = GETCMP1_(Transform);
	
	// reset speed at the beggining
	tr_->setVel(Vector2D(0, 0));
}

/*
Updates position, reduces speed and checks for bounce
with the screen limits
*/
void FighterMotion::update() {

	tr_->setPos(tr_->getPos() + tr_->getVel());
	tr_->setVel(tr_->getVel() * reduceRate_);

	if (!insideBordersX()) {
		tr_->setVelX(tr_->getVel().getX() * -1);
	}
	if (!insideBordersY()) {
		tr_->setVelY(tr_->getVel().getY() * -1);
	}
}

/*
Checks whether the new position would be out of the screen
(Y axis) to make the Fighter bounce
*/
bool FighterMotion::insideBordersX() const
{
	double nextPosX = (tr_->getPos() + tr_->getVel()).getX();

	// AABB collision check
	return nextPosX + tr_->getW() < game_->getWindowWidth() && nextPosX > 0;
}

/*
Checks whether the new position would be out of the screen
(X axis) to make the Fighter bounce
*/
bool FighterMotion::insideBordersY() const
{
	double nextPosY = (tr_->getPos() + tr_->getVel()).getY();

	// AABB collision check
	return  nextPosY + tr_->getH() < game_->getWindowHeight() && nextPosY > 0;
}
