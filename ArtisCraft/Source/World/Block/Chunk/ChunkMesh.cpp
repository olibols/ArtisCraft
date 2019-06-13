#include "ChunkMesh.h"
#include "../../Constants.h"

ChunkMesh::ChunkMesh()
{
	_mesh = new Mesh;
	_model = new Model;
}



void ChunkMesh::addBlock(std::vector<GLfloat> textureCoords, sf::Vector3i chunkPosition, sf::Vector3i blockPosition)
{
	_mesh->textureCoords.insert(_mesh->textureCoords.end(), textureCoords.begin(), textureCoords.end());

	Mesh cubeMesh;
	cubeMesh.vertexPositions = {
		//Back
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,

		//Front
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,

		//Right
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,

		//Left
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,

		//Top
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,

		//Bottom
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1.
	};


	for (int i = 0, index = 0; i < 24; ++i) {
		_mesh->vertexPositions.push_back(cubeMesh.vertexPositions[index++] + chunkPosition.x * CHUNK_SIZE + blockPosition.x);
		_mesh->vertexPositions.push_back(cubeMesh.vertexPositions[index++] + chunkPosition.y * CHUNK_SIZE + blockPosition.y);
		_mesh->vertexPositions.push_back(cubeMesh.vertexPositions[index++] + chunkPosition.z * CHUNK_SIZE + blockPosition.z);
	}


	for (int i = 0; i < 6; i++) {
		_mesh->indices.insert(_mesh->indices.end(), {
		_indiceCount,
		_indiceCount + 1,
		_indiceCount + 2,

		_indiceCount + 2,
		_indiceCount + 3,
		_indiceCount
			});

		_indiceCount += 4;
	}

}

void ChunkMesh::updateMesh()
{
	_model->addData(*_mesh);

	_mesh->indices.clear();
	_mesh->textureCoords.clear();
	_mesh->vertexPositions.clear();

	_indiceCount = 0;
}

Model ChunkMesh::getModel()
{
	return *_model;
}
