#include "Context.h"
#include "Renderer/Shaders/ShaderProgram.h"
#include "Model.h"
#include "Renderer/Texture/BasicTexture.h"

class Application {
public:
	Application(std::string windowName);

	sf::RenderWindow* getWindow();

	void runLoop();

	void initialiseScene();
	void renderScene();
	void releaseScene();

	void handleInput();

private:
	RenderContext* _context = nullptr;

	ShaderProgram* _shader = nullptr;

	Model* _quadModel = nullptr;

	BasicTexture* _texture = new BasicTexture("dirt");
};