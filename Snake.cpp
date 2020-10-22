#include "Snake.h"
#include "Circle.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define min(x, y) (x < y ? x : y)

bool Snake::Initialize()
{
	if (!Game::Initialize()) {
		return false;
	}

	if (TTF_Init() != 0) {
		SDL_Log("Unable to initialize TTF: %s", TTF_GetError());
		return false;
	}

	font = TTF_OpenFont(FONT, FONT_SIZE);
	if (!font) {
		SDL_Log("Failed to load font: %s", TTF_GetError());
		return false;
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	music = Mix_LoadMUS(MUSIC);
	turnSound = Mix_LoadWAV(TURN_SOUND);
	eatSound = Mix_LoadWAV(EAT_SOUND);
	bangSound = Mix_LoadWAV(BANG_SOUND);

	highScore = 0;

	srand(time(NULL));
	ResetGame();

	return true;
}

void Snake::Shutdown()
{
	TTF_CloseFont(font);
	TTF_Quit();
	Mix_Quit();
	Game::Shutdown();
}

void Snake::ResetGame()
{
	gameOver = false;

	snakeLength = INITIAL_LENGTH;
	snake.clear();
	for (int i = 0; i <= snakeLength; ++i) {
		snake.push_back(Cell(3 + i, 5));
	}
	progress = 0;
	direction = Cell(1, 0);
	prevDirection = direction;

	fruitPos = Cell(12, 5);

	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(music, -1);
	} else {
		Mix_ResumeMusic();
	}
}

void Snake::ProcessKeydown(SDL_Keycode sym)
{
	if (gameOver) {
		if (sym == SDLK_SPACE) {
			ResetGame();
		}
		return;
	}

	if (sym == SDLK_UP) {
		direction = Cell(0, -1);
	} else if (sym == SDLK_DOWN) {
		direction = Cell(0, 1);
	} else if (sym == SDLK_LEFT) {
		direction = Cell(-1, 0);
	} else if (sym == SDLK_RIGHT) {
		direction = Cell(1, 0);
	}
	if (!(direction == prevDirection)) {
		prevDirection = direction;
		Mix_PlayChannel(-1, turnSound, 0);
	}
}

void Snake::UpdateGame(float deltaTime)
{
	if (gameOver) {
		return;
	}

	progress += deltaTime * 4;

	if (progress >= 0.3f) {
		Cell head = snake.back();
		if ((head.x < 0 || head.x >= SCREEN_WIDTH / CELL_SIZE) ||
			(head.y < 0 || head.y >= SCREEN_HEIGHT / CELL_SIZE) ||
			std::find(snake.begin() + 1, snake.end() - 1, head) != snake.end() - 1) {
			gameOver = true;
			Mix_PauseMusic();
			Mix_PlayChannel(-1, bangSound, 0);
		}
	}

	if (progress >= 1.0f) {
		progress -= 1.0f;
		if (snake.size() > snakeLength) {
			snake.pop_front();
		}
		Cell head = snake.back();
		snake.push_back(head + direction);

		if (head == fruitPos) {
			++snakeLength;
			do {
				fruitPos.x = rand() % (SCREEN_WIDTH / CELL_SIZE);
				fruitPos.y = rand() % (SCREEN_HEIGHT / CELL_SIZE);
			} while (std::find(snake.begin(), snake.end(), fruitPos) != snake.end());
			Mix_PlayChannel(-1, eatSound, 0);
		}
	}
}

void Snake::GenerateOutput()
{
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

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillCircle(renderer,
		fruitPos.x * CELL_SIZE + CELL_SIZE / 2,
		fruitPos.y * CELL_SIZE + CELL_SIZE / 2,
		SNAKE_RADIUS);

	SDL_SetRenderDrawColor(renderer, 0, 64, 255, 255);
	for (int i = 0; i < snake.size() - 1; ++i) {
		Cell cell = snake[i];
		Cell next = snake[i + 1];
		int x = cell.x * CELL_SIZE + CELL_SIZE / 2;
		int y = cell.y * CELL_SIZE + CELL_SIZE / 2;
		int x2 = next.x * CELL_SIZE + CELL_SIZE / 2;
		int y2 = next.y * CELL_SIZE + CELL_SIZE / 2;
		if (i == 0 && snake.size() == snakeLength + 1) {
			x += static_cast<int>(roundf((x2 - x) * progress));
			y += static_cast<int>(roundf((y2 - y) * progress));
		} else if (i == snake.size() - 2) {
			x2 = x + static_cast<int>(roundf((x2 - x) * progress));
			y2 = y + static_cast<int>(roundf((y2 - y) * progress));
		}
		SDL_RenderFillCircle(renderer, x, y, SNAKE_RADIUS);

		SDL_Rect rect = { min(x, x2), min(y, y2), abs(x2 - x), abs(y2 - y) };
		if (cell.x == next.x) {
			rect.x -= SNAKE_RADIUS;
			rect.w = SNAKE_RADIUS * 2 + 1;
		} else {
			rect.y -= SNAKE_RADIUS;
			rect.h = SNAKE_RADIUS * 2 + 1;
		}
		SDL_RenderFillRect(renderer, &rect);

		if (i == snake.size() - 2) {
			x = x2;
			y = y2;
			if (gameOver) {
				SDL_SetRenderDrawColor(renderer, 192, 0, 255, 255);
			}
			SDL_RenderFillCircle(renderer, x, y, SNAKE_RADIUS);

			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			if (cell.x == next.x) {
				SDL_RenderFillCircle(renderer, x - SNAKE_RADIUS / 2, y, SNAKE_RADIUS / 4);
				SDL_RenderFillCircle(renderer, x + SNAKE_RADIUS / 2, y, SNAKE_RADIUS / 4);
			} else {
				SDL_RenderFillCircle(renderer, x, y - SNAKE_RADIUS / 2, SNAKE_RADIUS / 4);
				SDL_RenderFillCircle(renderer, x, y + SNAKE_RADIUS / 2, SNAKE_RADIUS / 4);
			}
		}
	}

	if (gameOver) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
		SDL_Rect rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

		int score = snakeLength - INITIAL_LENGTH;
		if (score > highScore) {
			highScore = score;
		}
		RenderText("Game Over", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5);
		std::stringstream scoreStream;
		scoreStream << "Score " << score;
		RenderText(scoreStream.str().c_str(), SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 5);
		std::stringstream highScoreStream;
		highScoreStream << "High Score " << highScore;
		RenderText(highScoreStream.str().c_str(), SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 5);
		RenderText("Press Space", SCREEN_WIDTH / 2, SCREEN_HEIGHT * 4 / 5);
	}

	SDL_RenderPresent(renderer);
}

void Snake::RenderText(const char* text, int x, int y)
{
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect textRect = { 0, 0, surface->w, surface->h };
	SDL_Rect rect = { x - surface->w / 2, y - surface->h / 2, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, &textRect, &rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
