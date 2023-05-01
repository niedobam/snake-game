#include "food.h"

const int CELL_WIDTH = 30;
const int WINDOW_WIDTH = 660;
const int WINDOW_HEIGHT = 660;

food::food()
{
    this->foodCoordinates.x = WINDOW_WIDTH/2 + CELL_WIDTH;
    this->foodCoordinates.y = WINDOW_HEIGHT/2 + CELL_WIDTH;
    this->foodCoordinates.w = CELL_WIDTH;
    this->foodCoordinates.h = CELL_WIDTH;
}

// Random food spawn positions
int food::getFoodSpawn()
{
    return (rand() % WINDOW_WIDTH/CELL_WIDTH) * 30;
}
