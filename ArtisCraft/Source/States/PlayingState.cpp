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
}

void PlayingState::update(float deltaTime)
{
}

void PlayingState::render()
{
}
