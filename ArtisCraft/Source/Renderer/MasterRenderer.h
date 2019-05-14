#include "QuadRenderer.h"

#include <SFML/Graphics.hpp>

class Camera;

class MasterRenderer {
public:
	void drawQuad(glm::vec3 position);

	void finishRender(sf::RenderWindow window, Camera camera);

private:
	QuadRenderer m_quadRenderer;
};