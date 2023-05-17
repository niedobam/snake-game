#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <string>
#include <vector>

#include "food.h"
#include "player.h"
#include "gameLoop.h"
#include "gameSettings.h"

int main(int argc, char *argv[])
{
    player snakePlayer;
    gameLoop snakeGame;
    food snakeFood;

    // Helper variables
    Uint32 start;
    Uint32 elapsedTime;
    int bestRoundScore = 0;
    bool gameRunning = true;
    bool exitGame = false;


    // Main game loop
    while (gameRunning) {
        start = SDL_GetTicks();
        srand(start);

        // Main game
        snakeGame.evaluateUserInput(&snakePlayer, &gameRunning, &exitGame);
        snakeGame.checkInternalCollision(&snakePlayer, &gameRunning);
        snakeGame.checkFoodCollision(&snakePlayer, &snakeFood);
        snakeGame.checkBordersCollisions(&snakePlayer, &gameRunning);
        snakeGame.updateSnakePosition(&snakePlayer, &snakeFood);
        snakeGame.renderFood(&snakeFood);
        snakeGame.renderPlayer(&snakePlayer);
        snakeGame.updateWindowTitle(&snakePlayer, &bestRoundScore);
        snakeGame.renderWindow();


        // Update best achieved score
        if (snakePlayer.snakeLength - 1 > bestRoundScore) {
            bestRoundScore = snakePlayer.snakeLength - 1;
        }

        // Reset game if terminating conditions have been met
        if (!gameRunning && !exitGame) {
            snakeGame.resetGameState(&snakePlayer, &snakeFood);
            gameRunning = true;
        }

        // Frame capping
        elapsedTime = SDL_GetTicks() - start;
        if (elapsedTime < settings::FPS) {
            SDL_Delay(1000/settings::FPS - elapsedTime);
        }
    }

    // Close SDL window
    snakeGame.cleanup();

    // Print game infor at the end
    printf("GAME OVER\n");
    printf("The Best Achieved Score: %d\n", bestRoundScore);

    return 0;
}
