#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL_rect.h>
#include <vector>

 class player {
    public:
        // SDL rect struct used for rendering a rectangle
        SDL_Rect rectangle;
  
        // Vectors for storing snake body cells
        std::vector<int> xSnakePositions;
        std::vector<int> ySnakePositions;
  
        // Variables for keeping track of last position of a snake
        int xPrevious;
        int yPrevious;

        int snakeLength;
        bool foodCollision;

        char direction;
        char previousDirection;

        // Constructor - initializing player variables
        player();
};

#endif
