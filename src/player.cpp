#include "player.h"

const int CELL_WIDTH = 30;
const int WINDOW_WIDTH = 660;
const int WINDOW_HEIGHT = 660;

player::player()
{
    this->rectangle.x = 0;
    this->rectangle.y = 0;
    this->rectangle.w = CELL_WIDTH;
    this->rectangle.h = CELL_WIDTH;

    this->xSnakePositions.push_back(0);
    this->ySnakePositions.push_back(0);

    this->xPrevious = 0;
    this->yPrevious = 0;

    this->foodCollision = false;

    this->direction = 's';
    this->previousDirection = 's';

    this->snakeLength = 1;
}

