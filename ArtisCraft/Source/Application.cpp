#include "Application.h"
#include <GLM.h>

Application::Application(std::string windowName)
{
	glEnable(GL_TEXTURE_2D);

	_context = new RenderContext(windowName, 800, 600);

	_shader = new ShaderProgram("BasicVertex", "BasicFragment");

	_quadModel = new Model();

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
	glUniform1i(glGetUniformLocation(_shader->getID(), "myTexture"), 0);	

	glDrawElements(GL_TRIANGLES, _quadModel->getIndicesCount(), GL_UNSIGNED_INT, 0);
}

void Application::releaseScene()
{
}

void Application::handleInput()
{
}
