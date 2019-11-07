#pragma once
#include <SFML/Graphics.hpp>
#include <array>

#include "SectionMesh.h"
#include "../WorldConstants.h"
#include "../Block/SectionBlock.h"

class Section {
public:
	Section(sf::Vector3i location);
	
	void setBlock(int x, int y, int z, SectionBlock block);
	SectionBlock getBlock(int x, int y, int z);

	inline sf::Vector3i getLocation() { return m_location; };
	inline SectionMesh& getMesh() { return m_mesh; };

	void buildMesh();
	void bufferMesh();

private:

	SectionMesh m_mesh;
	std::array<SectionBlock, SECTION_SIZE> m_blocks;

	sf::Vector3i m_location;
	sf::Vector3i toWorldPos(int x, int y, int z);

	bool outOfBounds(int value);
	int getIndex(int x, int y, int z);

};