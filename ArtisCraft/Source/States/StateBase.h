#pragma once

class Application;

class StateBase {
	StateBase(Application& app) : m_pApplication(&app) {};

	virtual ~StateBase() = default;

	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	virtual void handleInput() = 0;

private:
	Application* m_pApplication;
};