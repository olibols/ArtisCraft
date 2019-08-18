#pragma once
#include "Chunk.h"
#include "ChunkMesh.h"
#include "../Block/BlockData.h"

class ChunkMeshBuilder {
public:

	ChunkMeshBuilder(Chunk& chunk);

	void build();

private:

	bool shouldMakeFace(sf::Vector3i blockPosition, TextureData texData);
	bool shouldMakeLayer(int y);
	bool isAdjSolid(int x, int y, int z);

	void addFace(std::vector<GLfloat> blockFace, sf::Vector2i texCoords, sf::Vector3i blockPosition, sf::Vector3i blockFacing);

	Chunk* _chunk = nullptr;
	ChunkMesh* _mesh = nullptr;
	TextureData* _texData = nullptr;

};