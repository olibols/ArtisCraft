#include "Context.h"
#include "Camera.h"
#include "Entity/Player.h"
#include "Renderer/RenderMaster.h"


class Application {
public:
	Application(std::string windowName);

	sf::RenderWindow* getWindow();

	void runLoop();

	void handleInput();

private:
	RenderContext* _context = nullptr;

	RenderMaster* _renderMaster = nullptr;

	

	Camera* _camera = nullptr;

	Player* _player = nullptr;
};