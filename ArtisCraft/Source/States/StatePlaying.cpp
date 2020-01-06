#include "StatePlaying.h"
#include "../Application.h"
#include "../Renderer/MasterRenderer.h"
#include "../Renderer/BlockRenderer.h"

#include <SFML/OpenGL.hpp>
#include <cstdio>
#include <memory>

StatePlaying::StatePlaying(Application & app) : StateBase(app), m_chunk({0, 0, 0})
{
	app.getCamera().hookEntity(m_player);

	m_chunk.buildMesh();
	m_chunk.bufferMesh();
}

void StatePlaying::update(float deltaTime)
{
	m_player.update(deltaTime);
	//printf("%f %f %f \n", m_player.position.x, m_player.position.y, m_player.position.z);
}

void StatePlaying::render(MasterRenderer& renderer)
{
	renderer.drawBlock({ 0, 0, 0 });
	renderer.drawChunk(m_chunk.getMesh());
	renderer.finishRender(m_pApplication->getContext().window, m_pApplication->getCamera());
}

void StatePlaying::handleInput(MasterRenderer& renderer)
{
	m_player.handleInput(m_pApplication->getContext().window);
}
