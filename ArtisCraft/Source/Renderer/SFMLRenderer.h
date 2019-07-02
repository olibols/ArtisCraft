#pragma once
#include <SFML/Graphics.hpp>

class SFMLRenderer {
public:
	void add(sf::Drawable& thing);

	void render(sf::RenderWindow& window);
private:

	std::vector<sf::Drawable*> _drawables;
};