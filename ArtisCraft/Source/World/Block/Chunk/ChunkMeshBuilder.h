#pragma once
#include "Chunk.h"
#include "ChunkMesh.h"
#include "../BlockData.h"

class ChunkMeshBuilder {
public:

	ChunkMeshBuilder(Chunk& chunk);

	void build(ChunkMesh& mesh);

private:

	bool shouldMakeFace(sf::Vector3i blockPosition, TextureData texData);

	void addFace(std::vector<GLfloat> blockFace, sf::Vector2i texCoords, sf::Vector3i blockPosition, sf::Vector3i blockFacing);

	Chunk* _chunk = nullptr;
	ChunkMesh* _mesh = nullptr;
	TextureData* _texData = nullptr;

};