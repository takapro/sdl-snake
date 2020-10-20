#pragma once
#include "Game.h"
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

	bool Initialize();

private:
	void ProcessKeyboard(const Uint8* state) override;
	void UpdateGame(float deltaTime) override;
	void GenerateOutput() override;

	int snakeSize;
	std::deque<Cell> snake;
	float progress;
	Cell direction;

	Cell fruitPos;
};
