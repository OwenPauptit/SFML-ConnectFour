#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "StateManager.hpp"
#include "InputManager.hpp"

namespace Aesel {

	struct GameData {
		StateManager stateMGR;
		sf::RenderWindow window;
		InputManager inputMGR;
	};

	typedef std::shared_ptr <GameData> GameDataRef;

	class Game {
	public:
		// contstuctor to create and run game
		Game(int width, int height, std::string title);
	private:
		// dt is the time for 1 frame, it is set to 1/60 which is 60fps
		const float dt = 1.0f / 60.0f;
		sf::Clock _clock;

		// Pointer to the classes that will be accessible by all
		GameDataRef _data = std::make_shared <GameData>();

		// game loop
		void Run();
	};
}
