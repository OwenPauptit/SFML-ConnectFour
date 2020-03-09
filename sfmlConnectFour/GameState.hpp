#pragma once
#include "State.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace Aesel {

	class GameState : public State {

	public:

		GameState(GameDataRef data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw();

	private:

		GameDataRef _data;

		sf::Sprite _background, _redWin, _yellWin;
		sf::Texture _backgroundTex, _redWinTex, _yellWinTex;
		sf::CircleShape _redCounter;
		sf::CircleShape _yellowCounter;
		sf::CircleShape _emptySpace;

		std::vector<std::vector<int>> _board;
		bool _moveMade, _mouseDown;
		int _col, _currentPlayer, winner;

		bool PlaceCounter(int player, int row);
		int CheckWin();
	};
}