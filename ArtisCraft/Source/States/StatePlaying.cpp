#include "StatePlaying.h"
#include "../Application.h"
#include "../Renderer/MasterRenderer.h"
#include "../Renderer/BlockRenderer.h"

#include <SFML/OpenGL.hpp>
#include <cstdio>
#include <memory>

StatePlaying::StatePlaying(Application & app) : StateBase(app), m_world(app.getCamera())
{
	app.getCamera().hookEntity(m_player);
}

void StatePlaying::update(float deltaTime)
{
	m_player.update(deltaTime);
	//printf("%f %f %f \n", m_player.position.x, m_player.position.y, m_player.position.z);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
		m_world.setBlock(0, 0, 0, BlockID::Air);
	}
}

void StatePlaying::render(MasterRenderer& renderer)
{
	m_world.render(renderer);
	renderer.finishRender(m_pApplication->getContext().window, m_pApplication->getCamera());
}

void StatePlaying::handleInput(MasterRenderer& renderer)
{
	m_player.handleInput(m_pApplication->getContext().window);
}
