#include "../Entity.h"

class Player : public Entity
{
public:
	Player();

	void handleInput();

	void update(float dt);

private:
	void keyboardInput();
	void mouseInput();
};