/* [SDL2] Draw and fill a circle
 * https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c
 *
 * Copyright (c) 2016 Gumichan01
 * The source code is under the MIT Licence (https://opensource.org/licenses/MIT)
 */

#include <SDL2/SDL.h>

int
SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius);

int
SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);
