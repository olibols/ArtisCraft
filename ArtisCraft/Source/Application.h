#include "Context.h"
#include "Renderer/Shaders/ShaderProgram.h"
#include "Model.h"
#include "Camera.h"
#include "Renderer/Texture/BasicTexture.h"
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

	Camera _camera;
};