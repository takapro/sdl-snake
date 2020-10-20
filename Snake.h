#pragma once
#include "Game.h"

class Snake : public Game {
public:
	static constexpr int CELL_SIZE = 64;

	bool Initialize();

private:
	void ProcessKeyboard(const Uint8* state) override;
	void UpdateGame(float deltaTime) override;
	void GenerateOutput() override;
};
