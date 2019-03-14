//
// Created by Santiago Alvarez Vargas on 2018-12-18.
//

#include "Board.h"
#include "common/utils/Logger.h"
#include <math.h>

Board::Board(unsigned int boardWidth, unsigned int boardHeight):boardWidth(boardWidth),boardHeight(boardHeight)
{
    //Fill the cells matrix
    for (int row = 0; row < boardHeight; ++row)
    {
        cells.push_back(std::vector<Cell>());
        for (int col = 0; col < boardWidth; ++col)
        {
            cells[row].push_back(Cell());
        }
    }
}
