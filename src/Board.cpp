//
// Created by Santiago Alvarez Vargas on 2018-12-18.
//

#include "Board.h"
#include "common/utils/Logger.h"
#include <math.h>

Board::Board(unsigned int columns, unsigned int rows):columns(columns),rows(rows)
{
    //Fill the cells matrix
    for (int row = 0; row < rows; ++row)
    {
        cells.emplace_back(std::vector<Cell>());
        for (int col = 0; col < columns; ++col)
        {
            cells[row].emplace_back(Cell());
        }
    }
}
