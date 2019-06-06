#pragma once
#include <GLM.h>


//This class just holds the values and matrixes etc, it does NOT do movement etc

glm::mat4 makeViewMatrix(glm::vec3 rot, glm::vec3 pos);
glm::mat4 makeModelMatrix(glm::vec3 position, glm::vec3 rotation);

class Camera {
public:
	Camera();

	void update();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();
	glm::mat4 getProjViewMatrix();
	glm::vec3 getPosition();
	glm::vec3 getRotation();

private:
	glm::vec3 _worldPosition = {0, 0, -5};
	glm::vec3 _rotation = { 0, 0, 0 };

	glm::mat4 _projMatrix;
	glm::mat4 _viewMatrix;
	glm::mat4 _projViewMatrix;
};