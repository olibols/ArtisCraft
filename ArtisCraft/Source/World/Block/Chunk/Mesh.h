#pragma once

#include "../../../Model.h"

class ChunkMesh {
public:
	ChunkMesh();

	void addFace();

private:
	std::vector<GLfloat> _texCoords;
};
