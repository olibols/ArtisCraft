#include "ChunkShader.h"

ChunkShader::ChunkShader() : BlockShader("ChunkVertex", "ChunkFragment")
{
	getUniforms();
}

void ChunkShader::getUniforms()
{
	BlockShader::getUniforms();
}