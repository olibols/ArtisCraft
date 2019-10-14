#include "Section.h"

Section::Section(sf::Vector3i location) : m_location(location)
{
}

void Section::setBlock(int x, int y, int z, SectionBlock block)
{

}

SectionBlock Section::getBlock(int x, int y, int z)
{
	return SectionBlock();
}

void Section::buildMesh()
{
}

void Section::bufferMesh()
{
}

sf::Vector3i Section::toWorldPos(int x, int y, int z)
{
	return sf::Vector3i();
}

bool Section::outOfBounds(int value)
{
	return false;
}

int Section::getIndex(int x, int y, int z)
{
	return 0;
}
