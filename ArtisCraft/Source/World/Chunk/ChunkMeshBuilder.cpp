#include "ChunkMeshBuilder.h"

SectionMeshBuilder::SectionMeshBuilder(Section & section)
{
	m_pSection = &section;
	m_pMesh = &section.
}

void SectionMeshBuilder::build()
{
}

bool SectionMeshBuilder::shouldMakeFace(sf::Vector3i blockPos)
{
	return false;
}

void SectionMeshBuilder::addFace(std::vector<GLfloat> face, sf::Vector2i texCoords, sf::Vector3i position, sf::Vector3i blockFacing, GLfloat cardinalLight)
{
}
