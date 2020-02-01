#pragma once

#include <SFML/System/Vector3.hpp>

class StructureBuilder;

class Structure {
public:
	virtual void build(StructureBuilder& builder, sf::Vector3i startPos) = 0;
protected:
	StructureBuilder* m_builder;
};