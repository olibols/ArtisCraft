#include "Cube.h"

Cube::Cube() {

}

Cube::~Cube() {

}

void Cube::create() {

}

void Cube::draw(glm::mat4 projection_matrix, glm::mat4 view_matrix)
{
	glUseProgram(programID);
	glBindVertexArray(vaoID);

	glActiveTexture(GL_TEXTURE0);
	this->getTexture("Create").bindTexture();
	unsigned int textureLocation = glGetUniformLocation(programID, "texture1");
	glUniform1i(textureLocation, 0);

	glUniformMatrix4fv(glGetUniformLocation(programID, "view_matrix"), 1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "projection_matrix"), 1, false, &projection_matrix[0][0]);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}