#pragma once
#include <GLM.h>
#include "Entity/Entity.h"


//This class just holds the values and matrixes etc, it does NOT do movement etc

glm::mat4 makeViewMatrix(glm::vec3 rot, glm::vec3 pos);
glm::mat4 makeModelMatrix(glm::vec3 position, glm::vec3 rotation);

class Camera : public Entity {
public:
	Camera();

	void update();

	void hookEntity(const Entity& entity);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();
	glm::mat4 getProjViewMatrix();

private:

	const Entity* _entity = nullptr;

	glm::mat4 _projMatrix;
	glm::mat4 _viewMatrix;
	glm::mat4 _projViewMatrix;
};