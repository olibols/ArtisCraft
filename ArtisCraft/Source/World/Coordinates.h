#pragma once

#include <unordered_map>
#include <SFML/System/Vector3.hpp>

struct ChunkPosHash {
	const std::size_t operator()(const sf::Vector3i &position) const
	{
		return (position.x * 88339) ^ (position.z * 91967) ^
			(position.z * 126323);
	}
};

sf::Vector3i worldToChunkPos(sf::Vector3i pos);
sf::Vector3i toChunkPos(sf::Vector3i pos);
sf::Vector3i toLocalBlockPos(sf::Vector3i pos);
sf::Vector3i toGlobalBlockPos(sf::Vector3i blockPos, sf::Vector3i chunkPos);

template <typename T>
using ChunkPosMap = std::unordered_map<sf::Vector3i, T, ChunkPosHash>;