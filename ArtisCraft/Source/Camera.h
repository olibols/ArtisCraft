#pragma once
#include "Entity.h"

#include <GLM.h>

class Camera : public Entity {
public:
	Camera();

	void update();
	void hookEntity(const Entity& entity);

	const glm::mat4 getViewMatrix();
	const glm::mat4 getProjMatrix();
	const glm::mat4 getProjViewMatrix();

private:
	const Entity* _entity;

	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	glm::mat4 _projViewMatrx;

};