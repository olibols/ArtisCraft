#include "Application.h"


Application::Application(std::string windowName)
{

	_context = new RenderContext(windowName, 1280, 720);
	_shader = new ShaderProgram("BasicVertex", "BasicFragment");
	_quadModel = new Model();

	_texture = new BasicTexture("dirt");

	Mesh test;
	test.vertexPositions = {
		-0.5,  0.5, 0,
		 0.5,  0.5, 0,
		 0.5, -0.5, 0,
		-0.5, -0.5, 0,
	};

	test.textureCoords = {
		0, 1,
		1, 1,
		1, 0,
		0, 0
	};

	test.indices = {
		0, 1, 2,
		2, 3, 0
	};

	_quadModel->addData(test);
}

void Application::runLoop()
{
	initialiseScene();
	while (true) {
		renderScene();

		_context->window.display();
		handleInput();
	}
}

void Application::initialiseScene()
{
	glClearColor(0, 0.5f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
}

void Application::renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	_shader->useProgram();
	_quadModel->bindVAO();
	_texture->bindTexture();

	glDrawElements(GL_TRIANGLES, _quadModel->getIndicesCount(), GL_UNSIGNED_INT, 0);
}

void Application::releaseScene()
{
}

void Application::handleInput()
{
}
