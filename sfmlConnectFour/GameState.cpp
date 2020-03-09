#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Aesel {

	GameState::GameState(GameDataRef data) : _data(data) {

	}

	void GameState::Init() {
		if (_backgroundTex.loadFromFile(BACKGROUND_FILEPATH)) {
			_background.setTexture(_backgroundTex);
		}
		else {
			std::cout << "Background could not load";
		}
		if (_redWinTex.loadFromFile(RED_WINS_FILEPATH)) {
			_redWin.setTexture(_redWinTex);
		}
		else {
			std::cout << "Red Win Image could not load";
		}
		if (_yellWinTex.loadFromFile(YELLOW_WINS_FILEPATH)) {
			_yellWin.setTexture(_yellWinTex);
		}
		else {
			std::cout << "Yellow Win Image could not load";
		}

		std::vector<int> row;

		_redCounter.setFillColor(sf::Color::Red);
		_yellowCounter.setFillColor(sf::Color::Yellow);
		_emptySpace.setFillColor(sf::Color::White);
		_redCounter.setRadius(COUNTER_SIZE / 2);
		_yellowCounter.setRadius(COUNTER_SIZE/ 2);
		_emptySpace.setRadius(COUNTER_SIZE / 2);

		for (int y = 0; y < 6; y++) {
			for (int x = 0; x < 7; x++) {
				row.push_back(0);
			}
			_board.push_back(row);
		}

		_currentPlayer = 1;
		_mouseDown = true;
	}

	void GameState::HandleInput() {
		sf::Event event;
		while (_data->window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				_data->window.close();
			}
			if (_data->inputMGR.isWindowClicked(sf::Mouse::Left, _data->window)) {
				if (!_mouseDown){

					if (winner != 0) {
						_data->stateMGR.AddState(StateRef(new GameState(_data)), true);
					}
					else {
						_col = _data->inputMGR.getColClicked(_board[0].size(), _data->window);
						_moveMade = true;
					}
				}
				_mouseDown = true;
			}
			else if (_mouseDown) {
				_mouseDown = false;
			}
		}
	}

	void GameState::Update(float dt) {
		if (_moveMade) {
			if (PlaceCounter(_currentPlayer, _col)) {
				_currentPlayer -= 2; _currentPlayer *= -1; _currentPlayer += 1;
				_moveMade = false;

				winner = CheckWin();

			}
		}
	}

	int GameState::CheckWin() {

		// horizonral
		for (int y = 0; y < _board.size(); y++) {
			for (int x = 0; x < _board[y].size() - 3; x++) {
				if (_board[y][x] != 0) {
					if (_board[y][x] == _board[y][x + 1] && _board[y][x + 2] == _board[y][x + 3] && _board[y][x] == _board[y][x + 3]) {
						return _board[y][x];
					}
				}
			}
		}

		// vertical
		for (int y = 0; y < _board.size() - 3; y++) {
			for (int x = 0; x < _board[0].size(); x++) {
				if (_board[y][x] != 0) {
					if (_board[y][x] == _board[y + 1][x] && _board[y + 2][x] == _board[y + 3][x] && _board[y][x] == _board[y + 3][x]) {
						return _board[y][x];
					}
				}
			}
		}

		// diagonal (top left to bottom right
		for (int y = 0; y < _board.size() - 3; y++) {
			for (int x = 0; x < _board[0].size() - 3; x++) {
				if (_board[y][x] != 0) {
					if (_board[y][x] == _board[y + 1][x + 1] && _board[y + 2][x + 2] == _board[y + 3][x + 3] && _board[y][x] == _board[y + 3][x + 3]) {
						return _board[y][x];
					}
				}
			}
		}

		// diagonal (top right to bottom left
		for (int y = _board.size()-1; y > 2; y--) {
			for (int x = 0; x < _board[0].size() - 3; x++) {
				if (_board[y][x] != 0) {
					if (_board[y][x] == _board[y - 1][x + 1] && _board[y - 2][x + 2] == _board[y - 3][x + 3] && _board[y][x] == _board[y - 3][x + 3]) {
						return _board[y][x];
					}
				}
			}
		}

		return 0;

	}

	bool GameState::PlaceCounter(int player, int col) {
		for (int y = _board.size() - 1; y >= 0; y--) {
			if (_board[y][col] == 0) {
				_board[y][col] = player;
				return true;;
			}
		}
		return false;

	}

	void GameState::Draw() {
		_data->window.clear();

		_data->window.draw(_background);
		for (int y = 0; y < _board.size(); y++) {
			for (int x = 0; x < _board[0].size(); x++) {
				if (_board[y][x] == 1) {
					_redCounter.setPosition(sf::Vector2f(x * COUNTER_SIZE, y * COUNTER_SIZE));
					_data->window.draw(_redCounter);
				}else if (_board[y][x] == 2) {
					_yellowCounter.setPosition(sf::Vector2f(x * COUNTER_SIZE, y * COUNTER_SIZE));
					_data->window.draw(_yellowCounter);
				}
				else {
					_emptySpace.setPosition(sf::Vector2f(x * COUNTER_SIZE, y * COUNTER_SIZE));
					_data->window.draw(_emptySpace);
				}
			}
		}

		if (winner == 1) {
			_data->window.draw(_redWin);
		}
		else if (winner == 2) {
			_data->window.draw(_yellWin);
		}

		_data->window.display();

		
	}
}