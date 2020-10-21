#pragma once
#include "Game.h"
#include <SDL2/SDL_ttf.h>
#include <deque>

struct Cell {
	int x;
	int y;

	Cell() {}
	Cell(int x, int y) : x(x), y(y) {}

	bool operator ==(const Cell &o) const { return x == o.x && y == o.y; }
	Cell operator +(const Cell &o) const { return Cell(x + o.x, y + o.y); }
};

class Snake : public Game {
public:
	static constexpr int CELL_SIZE = 64;
	static constexpr int SNAKE_RADIUS = CELL_SIZE * 3 / 8;

	static constexpr int INITIAL_LENGTH = 4;

	bool Initialize();
	void Shutdown();

private:
	void ResetGame();

	void ProcessKeyboard(const Uint8* state) override;
	void UpdateGame(float deltaTime) override;
	void GenerateOutput() override;

	void RenderText(const char* text, int x, int y);

	TTF_Font *font;

	int highScore;
	bool gameOver;

	int snakeLength;
	std::deque<Cell> snake;
	float progress;
	Cell direction;

	Cell fruitPos;
};
