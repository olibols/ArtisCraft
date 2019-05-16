#include "BaseState.h"

class PlayingState : public BaseState {
public:
	PlayingState(Application &app);

	void handleEvent(sf::Event e);
	void handleInput();

	void update(float deltaTime);
	void render(MasterRenderer& renderer);
};