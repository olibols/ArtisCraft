#pragma once
#include "Settings.h"
#include "Entity/Entity.h"
#include <includes.h>

glm::mat4 makeModelMatrix(glm::vec3 position, glm::vec3 rotation);

class Camera : public Entity {
public:
	Camera();

	void update();

	void hookEntity(const Entity& entity);

	void newFov(float value);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();
	glm::mat4 getProjViewMatrix();

private:

	const Entity* _entity = nullptr;

	glm::mat4 _projMatrix;
	glm::mat4 _viewMatrix;
	glm::mat4 _projViewMatrix;
};