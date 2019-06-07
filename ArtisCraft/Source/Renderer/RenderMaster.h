#pragma once
#include <GLM.h>
#include <SFML/Graphics.hpp>
#include "../Camera.h"
#include "CubeRenderer.h"

class RenderMaster {
public:
	void drawCube(glm::vec3 position);

	void finishRender(sf::RenderWindow& window, Camera& camera);

private:
	CubeRenderer _cubeRenderer;

};