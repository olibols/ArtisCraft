#include "Context.h"
#include "Camera.h"
#include "Entity/Player.h"
#include "Renderer/RenderMaster.h"
#include "States/PlayingState.h"


class Application {
public:
	Application(std::string windowName);

	inline sf::RenderWindow& getWindow() { return _context->window; };
	inline Camera& getCamera() { return *_camera; };

	void runLoop();

	void handleInput();

private:

	std::vector<std::unique_ptr<BaseState>> _states;

	RenderContext* _context = nullptr;
	RenderMaster* _renderMaster = nullptr;
	Camera* _camera = nullptr;
};