#pragma once
#include <SDL2/SDL.h>

class Game {
public:
	static constexpr const char* WINDOW_TITLE = "Snake Game (CMPT 1267 Project 2)";

	static constexpr int SCREEN_WIDTH = 1024;
	static constexpr int SCREEN_HEIGHT = 768;

	bool Initialize();
	void RunLoop();
	void Shutdown();

protected:
	void ProcessInput();
	void UpdateGame();

	virtual void ProcessKeyboard(const Uint8* state) = 0;
	virtual void UpdateGame(float deltaTime) = 0;
	virtual void GenerateOutput() = 0;

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool isRunning;
	int ticksCount;
};
