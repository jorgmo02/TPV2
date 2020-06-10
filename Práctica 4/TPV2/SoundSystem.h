#pragma once
#include "System.h"
#include "AudioManager.h"

class SoundSystem : public System
{
public:
	SoundSystem();

	void init() override;
	virtual void recieve(const msg::Message& msg) override;

private:
	AudioManager* audioMngr_;
};