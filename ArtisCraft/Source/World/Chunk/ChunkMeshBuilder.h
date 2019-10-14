#pragma once

#include "Section.h"
#include "SectionMesh.h"

class SectionMeshBuilder {
public:
	SectionMeshBuilder(Section& section);

	void build();

private:
	bool shouldMakeFace(sf::Vector3i blockPos);
	void addFace(std::vector<GLfloat> face, sf::Vector2i texCoords, sf::Vector3i position, sf::Vector3i blockFacing, GLfloat cardinalLight);

	Section* m_pSection;
	SectionMesh* m_pMesh;
	
};