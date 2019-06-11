#pragma once
#include "Chunk.h"

class TextureData;

class ChunkBuildMesh {
public:
	ChunkBuildMesh(Chunk& chunk);

	void buildMesh(ChunkMesh chunkMesh);
private:

	void addMeshToFace(std::vector<GLfloat> face, sf::Vector2i textureCoords, sf::Vector2i blockPosition, sf::Vector2i blockFacint);

	void shouldMakeFace(sf::Vector3i adjBlock, TextureData texData);

	int faces = 0;

	Chunk* _chunk = nullptr;
	ChunkMesh* _mesh = nullptr;
	TextureData* _textureData = nullptr;
};