#pragma once
#include "Settings.h"
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

	void newFov(float value);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();
	glm::mat4 getProjViewMatrix();

private:

	const Entity* m_pEntity = nullptr;

	glm::mat4 m_projMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projViewMatrix;
};