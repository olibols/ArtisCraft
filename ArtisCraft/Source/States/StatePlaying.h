#pragma once
#include "StateBase.h"

class StatePlaying : public StateBase {
public:
	StatePlaying(Application& app);

	void update(float deltaTime) override;
	void render() override;
	void handleInput() override;

private:

};