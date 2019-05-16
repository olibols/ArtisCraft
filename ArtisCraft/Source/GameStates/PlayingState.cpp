#include "PlayingState.h"

#include "../Renderer/MasterRenderer.h"

PlayingState::PlayingState(Application &app) : BaseState(app) {};

void PlayingState::handleEvent(sf::Event e)
{

}

void PlayingState::handleInput()
{

}

void PlayingState::update(float deltaTime)
{

}

void PlayingState::render(MasterRenderer& renderer)
{
	static sf::Clock c;
	static float lastTime = 0;
	float timeNow = c.getElapsedTime().asSeconds();
	auto dt = timeNow - lastTime;
	lastTime = timeNow;



	renderer.drawQuad({ 0, 0, std::sin(timeNow) * 3 });
}