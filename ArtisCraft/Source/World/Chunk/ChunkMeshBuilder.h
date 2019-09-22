#pragma once
#include "Chunk.h"
#include "ChunkMesh.h"
#include "../Block/BlockData.h"

inline float testao(bool side1, bool side2, float corner) {
	if (side1 && side2) {
		return 0;
	}
	return 3 - (side1 + side2 + corner);
}

class ChunkMeshBuilder {
public:

	ChunkMeshBuilder(Chunk& chunk);

	void build();

private:

	bool shouldMakeFace(sf::Vector3i blockPosition, TextureData texData);
	bool shouldMakeLayer(int y);
	bool isAdjSolid(int x, int y, int z);

	void addFace(std::vector<GLfloat> blockFace, sf::Vector2i texCoords, sf::Vector3i blockPosition, sf::Vector3i blockFacing, GLfloat cardinalLight);

	Chunk* _chunk = nullptr;
	ChunkMesh* _mesh = nullptr;
	TextureData* _texData = nullptr;

};