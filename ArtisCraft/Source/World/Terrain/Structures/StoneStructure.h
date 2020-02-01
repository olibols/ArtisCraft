#pragma once

#include "../StructureBuilder.h"
#include "Structure.h"

class StoneStructure : public Structure {
public:
	void build(StructureBuilder& builder, sf::Vector3i startPos) override;
private:
};