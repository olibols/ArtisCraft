#pragma once
#include <SFML/Graphics.hpp>

class RenderMaster;
class Application;

class BaseState {
public:
	BaseState(Application& app) : _application(&app) {};

	virtual ~BaseState() = default;

	virtual void handleEvent(sf::Event event) = 0;
	virtual void handleInput() = 0;

	virtual void update(float deltaTime) = 0;


	virtual void render(RenderMaster& renderer) = 0;

protected:
	Application* _application;

};