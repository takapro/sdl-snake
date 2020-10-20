#include "Snake.h"
#include "Circle.h"

bool Snake::Initialize()
{
	if (!Game::Initialize()) {
		return false;
	}

	snakeSize = 4;
	for (int i = 0; i < snakeSize; i++) {
		snake.push_back(Cell(3 + i, 5));
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

	SDL_SetRenderDrawColor(renderer, 0, 64, 255, 255);
	for (int i = 0; i < snake.size(); ++i) {
		Cell cell = snake[i];
		int x = cell.x * CELL_SIZE + CELL_SIZE / 2;
		int y = cell.y * CELL_SIZE + CELL_SIZE / 2;
		SDL_RenderFillCircle(renderer, x, y, SNAKE_RADIUS);

		if (i < snake.size() - 1) {
			Cell next = snake[i + 1];
			SDL_Rect rect = { x, y, CELL_SIZE, CELL_SIZE };
			if (cell.x == next.x) {
				rect.x -= SNAKE_RADIUS;
				rect.y -= cell.y > next.y ? CELL_SIZE : 0;
				rect.w = SNAKE_RADIUS * 2 + 1;
			} else {
				rect.x -= cell.x > next.x ? CELL_SIZE : 0;
				rect.y -= SNAKE_RADIUS;
				rect.h = SNAKE_RADIUS * 2 + 1;
			}
			SDL_RenderFillRect(renderer, &rect);
		} else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			if (cell.x == snake[i - 1].x) {
				SDL_RenderFillCircle(renderer, x - SNAKE_RADIUS / 2, y, SNAKE_RADIUS / 4);
				SDL_RenderFillCircle(renderer, x + SNAKE_RADIUS / 2, y, SNAKE_RADIUS / 4);
			} else {
				SDL_RenderFillCircle(renderer, x, y - SNAKE_RADIUS / 2, SNAKE_RADIUS / 4);
				SDL_RenderFillCircle(renderer, x, y + SNAKE_RADIUS / 2, SNAKE_RADIUS / 4);
			}
		}
	}

	SDL_RenderPresent(renderer);
}
