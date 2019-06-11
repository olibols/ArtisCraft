#pragma once
#include <SFML/Graphics.hpp>


struct AdjacentPositions
{
	void update(int x, int y, int z)
	{
		up = { x,     y + 1,  z };
		down = { x,     y - 1,  z };
		left = { x - 1, y,      z };
		right = { x + 1, y,      z };
		front = { x,     y,      z + 1 };
		back = { x,     y,      z - 1 };
	}

	sf::Vector3i up;
	sf::Vector3i down;
	sf::Vector3i left;
	sf::Vector3i right;
	sf::Vector3i front;
	sf::Vector3i back;
};