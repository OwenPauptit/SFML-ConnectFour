#pragma once

#include <SFML/Graphics.hpp>

namespace Aesel {
	class InputManager {
	public:
		InputManager() {}
		~InputManager() {}

		bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

		bool isWindowClicked(sf::Mouse::Button button, sf::RenderWindow& window);

		int getColClicked(int cols, sf::RenderWindow& window);

		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};
}