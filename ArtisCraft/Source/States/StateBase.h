#pragma once
#include <SFML/Graphics.hpp>

#include "../Camera.h"

class Application;

class StateBase {
public:
	StateBase(Application& app) : _application(&app) {};

	virtual ~StateBase() = default;

	virtual void handleEvent(sf::Event event) = 0;
	virtual void handleInput() = 0;

	virtual void update(float deltaTime) = 0;


	virtual void render() = 0;

protected:
	Application* _application;

};