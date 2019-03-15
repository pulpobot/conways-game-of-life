//
// Created by Santiago Alvarez Vargas on 2018-12-18.
//

#ifndef CONWAYS_GAME_OF_LIFE_BOARD_H
#define CONWAYS_GAME_OF_LIFE_BOARD_H

#include <vector>
#include "Cell.h"

class Board
{
public:
    Board(unsigned int columns = DEFAULT_BOARD_WIDTH, unsigned int rows = DEFAULT_BOARD_HEIGHT);
    unsigned int columns;
    unsigned int rows;

private:
    const static unsigned int DEFAULT_BOARD_WIDTH = 80;
    const static unsigned int DEFAULT_BOARD_HEIGHT = 45;
    std::vector<std::vector<Cell>> cells;
};


#endif //CONWAYS_GAME_OF_LIFE_BOARD_H
