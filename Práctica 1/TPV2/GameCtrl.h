#pragma once

#include "Component.h"
#include "ScoreManager.h"
#include "Transform.h"

class GameCtrl: public Component {
public:
	GameCtrl();
	virtual ~GameCtrl();
	void init() override;
	void update() override;
	void draw() override;
private:
	ScoreManager *scoreManager_;
};

