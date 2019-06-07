#pragma once
#include "Entity.h"

class Player : public Entity {
public:
	Player();

	void handleInput();
	
	void update(float deltaTime);

private:
	void mouseInput();
	void keyboardInput();

	glm::vec3 _velocity = {0, 0, 0};
};