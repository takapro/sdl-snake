#include "Snake.h"

bool Snake::Initialize()
{
	if (!Game::Initialize()) {
		return false;
	}

	return true;
}

void Snake::ProcessKeyboard(const Uint8* state)
{
}

void Snake::UpdateGame(float deltaTime)
{
}

void Snake::GenerateOutput()
{
	SDL_RenderClear(renderer);

	for (int y = 0; y < SCREEN_HEIGHT; y += CELL_SIZE) {
		for (int x = 0; x < SCREEN_WIDTH; x += CELL_SIZE) {
			if ((x + y) / CELL_SIZE % 2 == 0) {
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			} else {
				SDL_SetRenderDrawColor(renderer, 0, 224, 0, 255);
			}
			SDL_Rect cell = { x, y, CELL_SIZE, CELL_SIZE };
			SDL_RenderFillRect(renderer, &cell);
		}
	}

	SDL_RenderPresent(renderer);
}
