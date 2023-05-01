#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "food.h"
#include "player.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>

class gameLoop {
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;

    public:
        gameLoop();
        void renderWindow();
        void renderFood(food *food);
        void renderPlayer(player *player);
        void evaluateUserInput(player *player, bool *isGameRunning, bool *exitGame);
        void updateSnakePosition(player *player, food *food);
        void updateWindowTitle(player *player, int *bestScore);
        void checkBordersCollisions(player *player, bool *isGameRunning);
        void checkInternalCollision(player *player, bool *gameRunning);
        void checkFoodCollision(player *player, food *food);
        void resetGameState(player *player, food *food);
        void cleanup();
};

#endif
