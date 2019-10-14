#pragma once

#include <SFML/Graphics.hpp>

#include "../../Model.h"

class SectionMesh {
public:
	SectionMesh();
	
	void addFace(std::vector<GLfloat> blockFace,
		std::vector<GLfloat> textureCoords,
		sf::Vector3i chunkPosition,
		sf::Vector3i blockPosition,
		GLfloat cardinalLight);

	void updateMesh();

	Model& getModel();

private:
	Mesh m_mesh;
	Model m_model;

	std::vector<GLfloat> m_light;

	GLuint m_indexIndex = 0;
};