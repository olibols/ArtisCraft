#include "Context.h"
#include "Camera.h"
#include "Renderer/QuadRenderer/QuadRenderer.h"
#include "Player/Player.h"

class Application {
public:
	Application(std::string name);

	void runLoop();

	Camera getCamera() { return m_camera; }

	sf::RenderWindow getWindow();

private:
	void handleEvents();

	RenderContext* m_context = new RenderContext(windowName, 1280, 720);
	QuadRenderer m_quadRenderer;
	Camera m_camera;

	Player m_player;

	std::string windowName;
};