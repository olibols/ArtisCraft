#include "QuadRenderer.h"

#include <SFML/Graphics.hpp>

class Camera;

class MasterRenderer {
public:
	void drawQuad(const glm::vec3& position);

	void finishRender(sf::RenderWindow& window, const Camera& camera);

private:
	QuadRenderer m_quadRenderer;
};