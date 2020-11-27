#pragma once
#include "Game.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
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

    static constexpr const char* FONT = "Font/Snake Chan.ttf";
    static constexpr int FONT_SIZE = 96;

    static constexpr const char* MUSIC = "Audio/bensound-ukulele.wav";
    static constexpr const char* TURN_SOUND = "Audio/click.wav";
    static constexpr const char* EAT_SOUND = "Audio/positive.wav";
    static constexpr const char* BANG_SOUND = "Audio/big-dart.wav";

    bool Initialize();
    void Shutdown();

private:
    void ResetGame();

    void ProcessKeydown(SDL_Keycode sym) override;
    void UpdateGame(float deltaTime) override;
    void GenerateOutput() override;

    void RenderText(const char* text, int x, int y);

    TTF_Font *font;

    Mix_Music *music;
    Mix_Chunk *turnSound;
    Mix_Chunk *eatSound;
    Mix_Chunk *bangSound;

    int highScore;
    bool gameOver;

    int snakeLength;
    std::deque<Cell> snake;
    float progress;
    Cell direction;
    Cell prevDirection;

    Cell fruitPos;
};
