#pragma once
#include <SFML/Graphics.hpp>

class Application;
class MasterRenderer;

class StateBase {
public:
	StateBase(Application& app) : m_pApplication(&app) {};

	virtual ~StateBase() = default;

	virtual void update(float deltaTime) = 0;
	virtual void render(MasterRenderer& renderer) = 0;
	virtual void handleInput(MasterRenderer& renderer) = 0;

protected:
	Application* m_pApplication;
};