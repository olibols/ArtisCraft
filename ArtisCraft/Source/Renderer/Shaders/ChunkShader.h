#pragma once
#include "BlockShader.h"

class ChunkShader : public BlockShader {
public:
	ChunkShader();
private:
	void getUniforms();
};