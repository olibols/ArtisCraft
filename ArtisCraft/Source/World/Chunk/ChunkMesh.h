#pragma once
#include "../../GL/Model.h"
#include "../WorldConstants.h"

#include <array>
#include <glm.hpp>
#include <SFML/Graphics.hpp>

struct ChunkMeshFace {
	std::array<GLfloat, 12> vertices;
	glm::vec3 color;
};

struct ChunkMesh {
	void addFace(const ChunkMeshFace face, const sf::Vector3i position);
	void bufferMesh();

	GLuint indiceCount = 0;
	
	Mesh mesh;
	Model model;

	sf::Vector3i worldPos;
};