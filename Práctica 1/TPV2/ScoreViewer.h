#pragma once

#include "Component.h"
#include "ScoreManager.h"

class ScoreViewer: public Component {
public:
	ScoreViewer();
	ScoreViewer(int scoreViewerColor);
	virtual ~ScoreViewer();
	void init() override;
	void draw() override;
private:
	int scoreViewerColor_;
	ScoreManager *scoreManager_;
};
