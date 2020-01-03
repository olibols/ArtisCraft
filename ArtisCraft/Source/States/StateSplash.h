#pragma once
#include "StateBase.h"

class StateSplash : public StateBase {
public:
	StateSplash(Application& app);

	void update(float deltaTime) override;
	void render(MasterRenderer& renderer) override;
	void handleInput(MasterRenderer& renderer) override;

private:

};