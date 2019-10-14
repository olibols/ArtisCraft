#include "SectionMesh.h"
#include "../WorldConstants.h"

SectionMesh::SectionMesh()
{

}

void SectionMesh::addFace(std::vector<GLfloat> blockFace, std::vector<GLfloat> textureCoords, sf::Vector3i chunkPosition, sf::Vector3i blockPosition, GLfloat cardinalLight)
{
	m_mesh.textureCoords.insert(m_mesh.textureCoords.end(), textureCoords.begin(), textureCoords.end());

	for (int i = 0, block = 0; i < 4; i++) {
		m_mesh.vertexPositions.push_back(blockFace[block++] + chunkPosition.x * SECTION_SIZE + blockPosition.x);
		m_mesh.vertexPositions.push_back(blockFace[block++] + chunkPosition.y * SECTION_SIZE + blockPosition.y);
		m_mesh.vertexPositions.push_back(blockFace[block++] + chunkPosition.z * SECTION_SIZE + blockPosition.z);

		m_light.push_back(cardinalLight);
	}

	m_mesh.indices.insert(m_mesh.indices.end(),
		{
		m_indexIndex,
		m_indexIndex + 1,
		m_indexIndex + 2,

		m_indexIndex + 2,
		m_indexIndex + 3,
		m_indexIndex
		});
	m_indexIndex += 4;
}

void SectionMesh::updateMesh()
{
	m_model.addData(m_mesh);
	m_model.addVBO(1, m_light);

	m_mesh.indices.clear();
	m_mesh.textureCoords.clear();
	m_mesh.vertexPositions.clear();
	m_light.clear();

	m_mesh.indices.shrink_to_fit();
	m_mesh.textureCoords.shrink_to_fit();
	m_mesh.vertexPositions.shrink_to_fit();
}

Model& SectionMesh::getModel()
{
	return m_model;
}
