#pragma once
#include <GLM.h>
#include "BlockID.h"

struct SectionBlock {
public:
	SectionBlock();

	SectionBlock(Block_t blockid);
	SectionBlock(BlockID blockid);

	bool operator ==(SectionBlock other) {
		return id == other.id;
	}

	bool operator !=(SectionBlock other) {
		return id != other.id;
	}

	Block_t id = 1;
};