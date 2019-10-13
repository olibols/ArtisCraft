#include "PlayingState.h"
#include "../Application.h"

PlayingState::PlayingState(Application & app) : StateBase(app)
{
	app.getCamera().hookEntity(m_player);
}

void PlayingState::handleEvent(sf::Event event)
{

}

void PlayingState::handleInput()
{
	m_player.handleInput(m_application->getWindow());
}

void PlayingState::update(float deltaTime)
{
	m_frameCounter.update();
}

void PlayingState::render(MasterRenderer& renderer)
{
	m_frameCounter.draw(renderer);
	renderer.finishRender(m_application->getWindow());
}

void PlayingState::onOpen()
{

}
