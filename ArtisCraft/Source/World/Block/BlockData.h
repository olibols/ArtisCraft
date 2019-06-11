#pragma once

#include <SFML/Graphics.hpp>


struct TextureData {
	sf::Vector2i texTopCoord;
	sf::Vector2i texSideCoord;
	sf::Vector2i texBottomCoord;
};

class BlockData {
public:
	BlockData(std::string fileName);

	TextureData& getTextureData();

private:
	TextureData _data;
};