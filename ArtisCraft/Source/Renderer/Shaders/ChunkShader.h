#pragma once
#include "BlockShader.h"


// Child of BlockShader. Contains the shader program for chunks
class ChunkShader : public BlockShader {
public:
	ChunkShader();
private:
	void getUniforms();
};