#include "player.h"
#include "gameSettings.h"

player::player()
{
    this->rectangle.x = 0;
    this->rectangle.y = 0;
    this->rectangle.w = settings::CELL_WIDTH;
    this->rectangle.h = settings::CELL_WIDTH;

    this->xSnakePositions.push_back(0);
    this->ySnakePositions.push_back(0);

    this->xPrevious = 0;
    this->yPrevious = 0;

    this->foodCollision = false;

    this->direction = 's';
    this->previousDirection = 's';

    this->snakeLength = 1;
}

