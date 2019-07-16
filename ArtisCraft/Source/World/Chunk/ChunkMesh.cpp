#include "ChunkMesh.h"
#include "../Constants.h"

ChunkMesh::ChunkMesh()
{
	_mesh = new Mesh;
	_model = new Model;
}



void ChunkMesh::addFace(std::vector<GLfloat> blockFace,
		std::vector<GLfloat> textureCoords,
		sf::Vector3i chunkPosition,
		sf::Vector3i blockPosition)
{
	_mesh->textureCoords.insert(_mesh->textureCoords.end(), textureCoords.begin(), textureCoords.end());

	for (int i = 0, block = 0; i < 4; i++) {
		_mesh->vertexPositions.push_back(blockFace[block++] + chunkPosition.x * CHUNK_SIZE + blockPosition.x);
		_mesh->vertexPositions.push_back(blockFace[block++] + chunkPosition.y * CHUNK_SIZE + blockPosition.y);
		_mesh->vertexPositions.push_back(blockFace[block++] + chunkPosition.z * CHUNK_SIZE + blockPosition.z);
	}

	_mesh->indices.insert(_mesh->indices.end(),
		{
		_indiceCount,
		_indiceCount + 1,
		_indiceCount + 2,

		_indiceCount + 2,
		_indiceCount + 3,
		_indiceCount
		});
	_indiceCount += 4;

	_faces++;
}

void ChunkMesh::updateMesh()
{
	_model->deleteData();

	_model->addData(*_mesh);

	_mesh->indices.clear();
	_mesh->textureCoords.clear();
	_mesh->vertexPositions.clear();

	_mesh->indices.shrink_to_fit();
	_mesh->textureCoords.shrink_to_fit();
	_mesh->vertexPositions.shrink_to_fit();

	_indiceCount = 0;
}

bool ChunkMesh::hasMesh()
{
	if (_faces > 0) return true;
	else return false;
}



Model ChunkMesh::getModel()
{
	return *_model;
}

void ChunkMesh::deleteModel()
{
	_model->deleteData();
}
