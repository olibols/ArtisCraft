#include "ChunkMesh.h"
#include "../../Constants.h"

ChunkMesh::ChunkMesh()
{
}

void ChunkMesh::addFace(std::vector<GLfloat> blockFace, std::vector<GLfloat> textureCoords, sf::Vector3i chunkPosition, sf::Vector3i blockPosition)
{
	auto& verticies = _mesh.vertexPositions;
	auto& texCoords = _mesh.textureCoords;
	auto& indices = _mesh.indices;

	texCoords.insert(texCoords.end(), textureCoords.begin(), textureCoords.end());

	for (int i = 0, index = 0; i < 4; ++i) {
		verticies.push_back(blockFace[index++] + chunkPosition.x * CHUNK_SIZE + blockPosition.x);
		verticies.push_back(blockFace[index++] + chunkPosition.y * CHUNK_SIZE + blockPosition.y);
		verticies.push_back(blockFace[index++] + chunkPosition.z * CHUNK_SIZE + blockPosition.z);
	}

	indices.insert(indices.end(), {
		_indiceCount,
		_indiceCount + 1,
		_indiceCount + 2,

		_indiceCount + 2,
		_indiceCount + 3,
		_indiceCount
		});

	_indiceCount += 4;
}

void ChunkMesh::updateMesh()
{
	_model.addData(_mesh);

	_mesh.vertexPositions.clear();
	_mesh.textureCoords.clear();
	_mesh.indices.clear();

	_indiceCount = 0;
}

Model ChunkMesh::getModel()
{
	return _model;
}
