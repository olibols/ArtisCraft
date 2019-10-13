#pragma once
#include <SFML/Graphics.hpp>
#include "../Renderer/MasterRenderer.h"

#include "../Camera.h"

class Application;

class StateBase {
public:
	StateBase(Application& app) : m_application(&app) {};

	virtual ~StateBase() = default;

	virtual void handleEvent(sf::Event event) = 0;
	virtual void handleInput() = 0;

	virtual void update(float deltaTime) = 0;
	
	virtual void render(MasterRenderer& renderer) = 0;
	virtual void onOpen() = 0;

protected:
	Application* m_application;

};