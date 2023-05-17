#include "food.h"
#include "gameSettings.h"

food::food()
{
    this->foodCoordinates.x = settings::WINDOW_WIDTH/2 + settings::CELL_WIDTH;
    this->foodCoordinates.y = settings::WINDOW_HEIGHT/2 + settings::CELL_WIDTH;
    this->foodCoordinates.w = settings::CELL_WIDTH;
    this->foodCoordinates.h = settings::CELL_WIDTH;
}

// Random food spawn positions
int food::getFoodSpawn()
{
    return (rand() % settings::WINDOW_WIDTH/settings::CELL_WIDTH) * 30;
}
