#include "Snake.h"

int main(int argc, char** argv)
{
    Snake game;

    if (game.Initialize()) {
        game.RunLoop();
    }

    game.Shutdown();

    return 0;
}
