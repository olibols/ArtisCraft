#include "ChunkMesh.h"

#include "../../GL/QuadPrimitive.h"
#include "../WorldConstants.h"

void ChunkMesh::addFace(ChunkMeshFace face, sf::Vector3i blockPos)
{
	int index = 0;
	for (int i = 0; i < 4; i++) {
		mesh.vertexPositions.push_back(face.vertices[index++] + worldPos.x * CHUNK_SIZE + blockPos.x);
		mesh.vertexPositions.push_back(face.vertices[index++] + worldPos.y * CHUNK_SIZE + blockPos.y);
		mesh.vertexPositions.push_back(face.vertices[index++] + worldPos.z * CHUNK_SIZE + blockPos.z);
	}
	mesh.vertexColors = QuadPrimitive::createQuadColors(face.color);

	mesh.indices.push_back(indiceCount);
	mesh.indices.push_back(indiceCount + 1);
	mesh.indices.push_back(indiceCount + 2);
	mesh.indices.push_back(indiceCount + 2);
	mesh.indices.push_back(indiceCount + 3);
	mesh.indices.push_back(indiceCount);
	indiceCount += 4;
}

void ChunkMesh::bufferMesh()
{
	model.addData(mesh);
}
