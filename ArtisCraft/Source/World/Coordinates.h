#pragma once

#include <unordered_map>
#include <SFML/System/Vector3.hpp>

struct ChunkPosHash {
	std::size_t operator()(const sf::Vector3i &position) const
	{
		return (position.x * 88339) ^ (position.z * 91967) ^
			(position.z * 126323);
	}
};

template <typename T>
using ChunkPosMap = std::unordered_map<sf::Vector3i, T, ChunkPosHash>;