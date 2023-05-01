#ifndef FOOD_H
#define FOOD_H

#include<SDL2/SDL_rect.h>

class food {
    public:
        SDL_Rect foodCoordinates;

        food();
        int getFoodSpawn();
};

#endif
