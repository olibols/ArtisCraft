#include "Context.h"
#include "Camera.h"
#include "Entity/Player.h"
#include "Renderer/QuadRenderer.h"


class Application {
public:
	Application(std::string windowName);

	sf::RenderWindow* getWindow();

	void runLoop();

	void handleInput();

private:
	RenderContext* _context = nullptr;

	QuadRenderer* _quadRenderer = nullptr;

	Camera* _camera = nullptr;

	Player* _player = nullptr;
};