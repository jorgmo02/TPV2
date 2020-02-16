#pragma once

#include "Component.h"
#include "ScoreManager.h"
#include "Transform.h"

class GameLogic: public Component {
public:
	GameLogic(Transform* cazaTR);
	virtual ~GameLogic();
	void init() override;
	void update() override;
private:
	Transform* cazaTR_;
	ScoreManager *scoreManager_;
};

