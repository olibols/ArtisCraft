#pragma once

#include "../BlockID.h"

struct ChunkBlock {
	ChunkBlock();

	ChunkBlock(BlockID block);

	bool operator ==(BlockID other) {
		return id == other;
	}

	bool operator ==(ChunkBlock other) {
		return id == other.id;
	}

	bool operator !=(BlockID other) {
		return id != other;
	}

	bool operator !=(ChunkBlock other) {
		return id != other.id;
	}

	void operator =(ChunkBlock other) {
		id = other.id;
	}

	BlockID id = BlockID::Air;
};