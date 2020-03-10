#pragma once

#include "Component.h"
#include "ScoreManager.h"
#include "Transform.h"
#include "AsteroidPool.h"
#include "Health.h"

class GameCtrl: public Component {
public:
	GameCtrl();
	GameCtrl(AsteroidPool* a, Health* h, int asteroidsGenerated);
	virtual ~GameCtrl();
	void init() override;
	void update() override;
	void draw() override;
private:
	int iniLifes_;
	int asteroidsGenerated_;
	AsteroidPool* pool_;
	Health* health_;
	ScoreManager *scoreManager_;
};

