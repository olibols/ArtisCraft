#pragma once

#include <unordered_map>
#include <functional>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Utils/RobinHash.h"

struct ChunkPosHash {
	const std::size_t operator()(const sf::Vector3i &position) const
	{
		return (position.x * 88339) ^ (position.z * 91967) ^
			(position.z * 126323);
	}

	const std::size_t operator()(const sf::Vector2i &position) const
	{
		return (position.x * 88339) ^ (position.y * 91967) ^
			(position.y * 126323);
	}
};

template<>
struct std::hash<sf::Vector2i>{
	size_t operator()(const sf::Vector2i& vect) const
	{
		std::hash<decltype(vect.x)> hasher;

		auto hash1 = hasher(vect.x);
		auto hash2 = hasher(vect.y);

		return std::hash<decltype(vect.x)>{}((hash1 ^ hash2) >> 2);
	}
};


sf::Vector3i worldToChunkPos(sf::Vector3i pos);
sf::Vector3i toChunkPos(sf::Vector3i pos);
sf::Vector3i toLocalBlockPos(sf::Vector3i pos);
sf::Vector3i toGlobalBlockPos(sf::Vector3i blockPos, sf::Vector3i chunkPos);

template <typename T>
using ChunkPosMap = robin_hood::unordered_map<sf::Vector3i, T, ChunkPosHash>;

template <typename T>
using ChunkHeightMap = robin_hood::unordered_map<sf::Vector2i, T, ChunkPosHash>;