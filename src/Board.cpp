//
// Created by Santiago Alvarez Vargas on 2018-12-18.
//

#include "Board.h"
#include "common/utils/Logger.h"
#include "common/event/EventSystem.h"
#include <math.h>
#include "events/ConwaysEvents.h"
#include <random>

Board::Board(unsigned int columns, unsigned int rows) : columns(columns), rows(rows)
{
    //Fill the cells matrix
    for (int row = 0; row < rows; ++row)
    {
        cells.emplace_back(std::vector<Cell>());
        previousCellsState.emplace_back(std::vector<Cell>());
        for (int col = 0; col < columns; ++col)
        {
            cells[row].emplace_back(Cell());
            previousCellsState[row].emplace_back(Cell());
        }
    }
}

void Board::Init()
{
    std::mt19937 m(std::time(NULL));
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < columns; ++col)
        {
            if (dist(m) > 0.75)
            {
                cells[row][col].alive = true;
                EventSystem::Instance().Dispatch(std::shared_ptr<CellUpdatedEvent>(new CellUpdatedEvent(row, col, true)));
            }
        }
    }
}

///Update the status of the cells
void Board::Update()
{

    /*
        Any live cell with fewer than two live neighbours dies, as if by underpopulation.
        Any live cell with two or three live neighbours lives on to the next generation.
        Any live cell with more than three live neighbours dies, as if by overpopulation.
        Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
     */

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < columns; ++col)
        {
            //TODO: Add a possibility to loop the border
            //rules apply simultaneously on every cell, so we need to store the previous state for reference in next iters
            previousCellsState[row][col].alive = cells[row][col].alive;
            unsigned int aliveNeighbours = AliveNeighbours(row, col, previousCellsState);

            //kill any living cell by underpopulation
            if(cells[row][col].alive && aliveNeighbours < 2)
            {
                cells[row][col].alive = false;
                EventSystem::Instance().Dispatch(std::shared_ptr<CellUpdatedEvent>(new CellUpdatedEvent(row, col, false)));
            }
            //kill any living cell by overpopulation
            else if(cells[row][col].alive && aliveNeighbours > 3)
            {
                cells[row][col].alive = false;
                EventSystem::Instance().Dispatch(std::shared_ptr<CellUpdatedEvent>(new CellUpdatedEvent(row, col, false)));
            }
            //turn any dead cell to a live cell by reproduction
            else if(!cells[row][col].alive && aliveNeighbours == 3)
            {
                cells[row][col].alive = true;
                EventSystem::Instance().Dispatch(std::shared_ptr<CellUpdatedEvent>(new CellUpdatedEvent(row, col, true)));
            }
        }
    }

}

unsigned int Board::AliveNeighbours(unsigned int row, unsigned int col, std::vector<std::vector<Cell>> &cellsRef)
{
    //assume border is dead cells
    unsigned int alive = 0;
    //left
    if (col > 0 && cellsRef[row][col - 1].alive)
    {
        ++alive;
    }

    //right
    if (col < columns - 1 && cellsRef[row][col + 1].alive)
    {
        ++alive;
    }

    //above left
    if (col > 0 && row > 0 && cellsRef[row - 1][col - 1].alive)
    {
        ++alive;
    }

    //above
    if (row > 0 && cellsRef[row - 1][col].alive)
    {
        ++alive;
    }

    //above right
    if (col < columns - 1 && row > 0 && cellsRef[row - 1][col + 1].alive)
    {
        ++alive;
    }

    //below left
    if (col > 0 && row < rows - 1 && cellsRef[row + 1][col - 1].alive)
    {
        ++alive;
    }

    //below
    if (row < rows - 1 && cellsRef[row + 1][col].alive)
    {
        ++alive;
    }

    //below right
    if (col < columns - 1 && row < rows - 1 && cellsRef[row + 1][col + 1].alive)
    {
        ++alive;
    }

    return alive;
}
