#include "Game.hpp"
#include "GameState.hpp"

namespace Aesel {

	// Creates an SFML window, and runs the game
	Game::Game(int width, int height, std::string title) {
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

		_data->stateMGR.AddState(StateRef( new GameState(_data)), true);

		this->Run();
	}

	// The Game loop
	void Game::Run() {

		// Time calculation values
		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds();

		float accumulator = 0.0f;


		// While the SFML window is open
		while (this->_data->window.isOpen()) {

			// Process any state changes
			this->_data->stateMGR.ProcessStateChanges();

			//Time calculations

			newTime = this->_clock.getElapsedTime().asSeconds();

			// Finds time since last frame
			frameTime = newTime - currentTime;

			// Limits the game time passed to 0.25 seconds
			if (frameTime > 0.25f) {
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			// while more time has passed since the last update than the length of one frame, handle inputs of the state, and update the state
			while (accumulator >= dt) {
				this->_data->stateMGR.GetActiveState()->HandleInput();

				this->_data->stateMGR.GetActiveState()->Update(dt);

				accumulator -= dt;
			}

			// Draw the state - interpolation gives the amount of frames passed since the last update
			interpolation = accumulator / dt;
			this->_data->stateMGR.GetActiveState()->Draw();

		}
	}
}