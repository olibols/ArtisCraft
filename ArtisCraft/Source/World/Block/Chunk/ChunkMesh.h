#pragma once
#include "../../../Model.h"
#include <SFML/Graphics.hpp>

class ChunkMesh {
public:
	ChunkMesh();

	void addBlock(std::vector<GLfloat> textureCoords,
		sf::Vector3i chunkPosition,
		sf::Vector3i blockPosition);

	void updateMesh();

	Model getModel();

private:

	GLuint _indiceCount = 0;

	Mesh* _mesh = nullptr;
	Model* _model = nullptr;

};