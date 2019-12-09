#pragma once

class Application;

class StateBase {
public:
	StateBase(Application& app) : m_pApplication(&app) {};

	virtual ~StateBase() = default;

	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void handleInput() = 0;

protected:
	Application* m_pApplication;
};