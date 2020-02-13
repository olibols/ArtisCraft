#include "StatePlaying.h"
#include "../Application.h"
#include "../Renderer/MasterRenderer.h"
#include "../Renderer/BlockRenderer.h"
#include "../Utils/Ray.h"

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
	
	/*for (Ray ray(m_player.position, m_player.rotation); ray.getLength() < 6; ray.step(0.1)){
		auto x = ray.getEnd().x;
		auto y = ray.getEnd().y;
		auto z = ray.getEnd().z;

		if (m_inputTimer.getElapsedTime().asSeconds() > 0.2) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				BlockID block = m_world.getBlock(x, y, z);
				if (block != BlockID::Air) {
					m_inputTimer.restart();
					m_world.psetBlock(ray.getEnd().x, ray.getEnd().y, ray.getEnd().z, BlockID::Air);
					break;
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				m_inputTimer.restart();
				m_world.psetBlock(m_rayPos.x, m_rayPos.y, m_rayPos.z, BlockID::Grass);
				break;
			}
		}

		m_rayPos = ray.getEnd();
	}*/

	if (m_inputTimer.getElapsedTime().asSeconds() > 0.2) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			for (Ray ray(m_player.position, m_player.rotation); ray.getLength() < 6; ray.step(0.1)) {
				BlockID block = m_world.getBlock(ray.getEnd().x, ray.getEnd().y, ray.getEnd().z);
				if (block != BlockID::Air) {
					m_inputTimer.restart();
					m_world.psetBlock(ray.getEnd().x, ray.getEnd().y, ray.getEnd().z, BlockID::Air);
					break;
				}
			}
		}
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
