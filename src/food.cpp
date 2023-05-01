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
void food::getFoodSpawn()
{
    int xFoodCoordinateCandidate = (rand() % WINDOW_WIDTH/CELL_WIDTH) * 30;
    int yFoodCoordinateCandidate = (rand() % WINDOW_WIDTH/CELL_WIDTH) * 30;
}
