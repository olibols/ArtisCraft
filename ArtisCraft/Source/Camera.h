#pragma once

#include <GLM.h>

class Camera {
public:
	Camera();

	void update();

	const glm::mat4 getViewMatrix();
};