#pragma once
#include "Chunk.h"
#include "ChunkMesh.h"
#include "../BlockData.h"

class ChunkMeshBuilder {
public:

	ChunkMeshBuilder(Chunk& chunk);

	void build(ChunkMesh& mesh);

private:

	Chunk* _chunk = nullptr;
	ChunkMesh* _mesh = nullptr;
	TextureData* _texData = nullptr;

};