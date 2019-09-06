#pragma once
#include "../../Model.h"
#include <SFML/Graphics.hpp>

class ChunkMesh {
public:
	ChunkMesh();

	void addFace(std::vector<GLfloat> blockFace,
		std::vector<GLfloat> textureCoords,
		sf::Vector3i chunkPosition,
		sf::Vector3i blockPosition,
		GLfloat cardinalLight);

	void updateMesh();

	bool hasMesh();

	Model& getModel();
	void deleteModel();

private:

	GLuint _indiceCount = 0;
	int _faces = 0;

	std::vector<GLfloat> _light;

	Mesh* _mesh;
	Model* _model;

};