#include "gameLoop.h"
#include "gameSettings.h"

#include <SDL2/SDL.h>
#include <string>
#include <vector>

gameLoop::gameLoop()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not be initialized\n\n");
    } else {
        printf("SDL successfully initialized\n\n");
    }

    this->window = nullptr;
    this->window = SDL_CreateShapedWindow("snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    this->renderer = nullptr;
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
}

// Renders entire gameLoop window
void gameLoop::renderWindow()
{
    SDL_SetWindowBordered(this->window, SDL_TRUE);
    SDL_SetRenderDrawColor(this->renderer, 192, 192, 192, 0xFF);
    SDL_RenderPresent(this->renderer);
    SDL_RenderClear(this->renderer);
}

// Modifies renderer object for food rendering
void gameLoop::renderFood(food *food)
{
    SDL_SetRenderDrawColor(this->renderer, 196, 30, 58, 255);
    SDL_RenderFillRect(this->renderer, &food->foodCoordinates);
}

// Modifies renderer object for player rendering
void gameLoop::renderPlayer(player *player)
{
    for (int i = 0; i < player->snakeLength; i++) {
        // Color snake head black
        if (i == 0) {
            SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        // Color every next snake cell different shade of green
        } else if (i % 2 == 0) {
            SDL_SetRenderDrawColor(this->renderer, 0, 102, 0, 255);
        } else {
            SDL_SetRenderDrawColor(this->renderer, 0, 153, 0, 255);
        }
        player->rectangle.x = player->xSnakePositions[i];
        player->rectangle.y = player->ySnakePositions[i];
        SDL_RenderFillRect(this->renderer, &player->rectangle);
    }
    SDL_RenderFillRect(this->renderer, &player->rectangle);
}

/* 'u' -> up direction
   'd' -> down direction
   'l' -> left direction
   'r' -> right direction
   's' -> snake is stationary - gameLoop is paused */
void gameLoop::evaluateUserInput(player *player, bool *isgameLoopRunning, bool *exitgameLoop)
{
    for(; SDL_PollEvent(&this->event);) {
        if (this->event.type == SDL_QUIT || this->event.key.keysym.sym == SDLK_q) {
            *isgameLoopRunning = false;
            *exitgameLoop = true;
        } else {
            switch(this->event.type) {
                case SDL_KEYDOWN:
                    player->previousDirection = player->direction;
                    switch(event.key.keysym.sym) {
                        case SDLK_UP:
                            player->direction = 'u';
                            break;
                        case SDLK_DOWN:
                            player->direction = 'd';
                            break;
                        case SDLK_LEFT:
                            player->direction = 'l';
                            break;
                        case SDLK_RIGHT:
                            player->direction = 'r';
                            break;
                        case SDLK_ESCAPE:
                            player->direction = 's';
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

// Updates position of all snake cells and evaluates food collisions
void gameLoop::updateSnakePosition(player *player, food *food)
{
    // Updates position of every snake cell
    if (player->direction != 's') {
        player->xPrevious = player->xSnakePositions.back();
        player->yPrevious = player->ySnakePositions.back();

        for (int i = player->snakeLength - 1; i > 0; i--) {
            player->xSnakePositions[i] = player->xSnakePositions[i - 1];
            player->ySnakePositions[i] = player->ySnakePositions[i - 1];
        }
    }

    // Updates position of the snake head based on user input, whilst preventing 180 degrees snake head direction change (from up to down, from left to right...)
    switch (player->direction) {
        case 'u':
            if (player->previousDirection == 'd') {
                player->ySnakePositions[0] += settings::CELL_WIDTH;
                player->direction = player->previousDirection;
            } else {
                player->ySnakePositions[0] -= settings::CELL_WIDTH;
            }
            break;
        case 'd':
            if (player->previousDirection == 'u') {
                player->ySnakePositions[0] -= settings::CELL_WIDTH;
                player->direction = player->previousDirection;
            } else {
                player->ySnakePositions[0] += settings::CELL_WIDTH;
            }
            break;
        case 'r':
            if (player->previousDirection == 'l') {
                player->xSnakePositions[0] -= settings::CELL_WIDTH;
                player->direction = player->previousDirection;
            } else {
                player->xSnakePositions[0] += settings::CELL_WIDTH;
            }
            break;
        case 'l':
            if (player->previousDirection == 'r') {
                player->xSnakePositions[0] += settings::CELL_WIDTH;
                player->direction = player->previousDirection;
            } else {
                player->xSnakePositions[0] -= settings::CELL_WIDTH;
            }
            break;
        case 's':
            break;
    }

    // Evaluates food collision - if snake and food collided, creates new snake cell
    if (player->foodCollision) {

        // Increment snake length
        player->snakeLength += 1;

        // Reset foodCollision variable
        player->foodCollision = false;

        // Append new snake cells
        player->xSnakePositions.push_back(player->xPrevious);
        player->ySnakePositions.push_back(player->yPrevious);

        // Find food spawn that is different that any snake tail positions
        int xFoodCoordinateCandidate = food->getFoodSpawn();
        int yFoodCoordinateCandidate = food->getFoodSpawn();
        while (true) {
            for (int i = 0; i < player->snakeLength; i++) {
                if (player->xSnakePositions[i] == xFoodCoordinateCandidate && player->ySnakePositions[i] == yFoodCoordinateCandidate) {
                    xFoodCoordinateCandidate = food->getFoodSpawn();
                    yFoodCoordinateCandidate = food->getFoodSpawn();
                    i = 0;
                }
            }
            break;
        }
        food->foodCoordinates.x = xFoodCoordinateCandidate;
        food->foodCoordinates.y = yFoodCoordinateCandidate;
    }
}

// Displays gameLoop state, actual and the best achieved score in the top window
void gameLoop::updateWindowTitle(player *player, int *bestScore)
{
    std::string gameLoopState;

    if (player->direction == 's') {
        gameLoopState = "Game Paused";
    } else {
        gameLoopState = "Game Running";
    }

    std::string title{gameLoopState + " | Snake Score: " + std::to_string(player->snakeLength - 1) + " | Best Score: " + std::to_string(*bestScore)};
    SDL_SetWindowTitle(this->window, title.c_str());
}

// Checks if snake has collided with the window border
void gameLoop::checkBordersCollisions(player *player, bool *isgameLoopRunning)
{
    bool xBoundsCondition = (player->xSnakePositions[0] > settings::WINDOW_WIDTH - settings::CELL_WIDTH) || (player->xSnakePositions[0] < 0);
    bool yBoundsCondition = (player->ySnakePositions[0] > settings::WINDOW_HEIGHT - settings::CELL_WIDTH) || (player->ySnakePositions[0] < 0);

    if (xBoundsCondition || yBoundsCondition) {
        *isgameLoopRunning = false;
    }
}

// Cheks if snake has collided with itself
void gameLoop::checkInternalCollision(player *player, bool *gameLoopRunning)
{
    for (int i = 1; i < player->snakeLength; i++) {
        if (player->xSnakePositions[0] == player->xSnakePositions[i] && player->ySnakePositions[0] == player->ySnakePositions[i]) {
            *gameLoopRunning = false;
        }
    }
}

// Checks if snake has collided with the food
void gameLoop::checkFoodCollision(player *player, food *food) {
    if (player->xSnakePositions.front() == food->foodCoordinates.x && player->ySnakePositions.front() == food->foodCoordinates.y) {
        player->foodCollision = true;
    }
}

// After one of the gameLoop over conditions is met resets gameLoop to default state
void gameLoop::resetGameState(player *player, food *food)
{
    player->rectangle.x = 0;
    player->rectangle.y = 0;
    player->rectangle.w = settings::CELL_WIDTH;
    player->rectangle.h = settings::CELL_WIDTH;

    player->xSnakePositions.clear();
    player->ySnakePositions.clear();
    player->xSnakePositions.push_back(0);
    player->ySnakePositions.push_back(0);

    player->xPrevious = 0;
    player->yPrevious = 0;
    player->foodCollision = false;
    player->direction = 's';
    player->snakeLength = 1;

    food->foodCoordinates.x = settings::WINDOW_WIDTH/2 + settings::CELL_WIDTH;
    food->foodCoordinates.y = settings::WINDOW_HEIGHT/2 + settings::CELL_WIDTH;
    food->foodCoordinates.w = settings::CELL_WIDTH;
    food->foodCoordinates.h = settings::CELL_WIDTH;
}

// SDL cleanup
void gameLoop::cleanup()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

