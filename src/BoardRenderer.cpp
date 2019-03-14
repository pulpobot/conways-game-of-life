//
// Created by Santiago Alvarez Vargas on 2019-03-14.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include "BoardRenderer.h"
#include "common/utils/Logger.h"

BoardRenderer::BoardRenderer(Board *board, sf::RenderWindow *window)
{
    this->window = window;
    this->board = board;

    isLandscape = true;
    //is portrait?
    if (window->getSize().y > window->getSize().x)
    {
        isLandscape = false;
    }

    CalculateCellSize();

    //TODO: I would like to be able to change the size through a debug menu, listen to events here
}

void BoardRenderer::Render()
{
    LinkedList<CellRenderer>::LinkedListNode * currentCellRenderer = cellRenderers.GetFirst();
    while (nullptr != currentCellRenderer)
    {
        currentCellRenderer->value->Draw(window);
        currentCellRenderer = currentCellRenderer->next;
    }
}

void BoardRenderer::CalculateCellSize()
{
    // The board is generated based on whenever the device is on portrait or landscape mode
    // We ensure we accommodate the amount of cells expected in the board

    cellSize = (window->getSize().x / (double) board->boardWidth);

    //TODO:Consider cell outline thickness
    verticalBorder = (window->getSize().x - cellSize * board->boardWidth) / 2;

    horizontalBorder = (window->getSize().y - cellSize * board->boardHeight) / 2;
    unsigned int boardHeightPixels = cellSize * board->boardHeight;
    if(window->getSize().y < boardHeightPixels)
    {
        //TODO: Rescale cells to fit, probably it means increasing black borders
        horizontalBorder = 0;
    }
    else
    {
    }

    cellRenderers.Clear();
    for (int row = 0; row < board->boardHeight; ++row)
    {
        for (int col = 0; col < board->boardWidth; ++col)
        {
            Logger::Debug("Cell at: " + std::to_string( horizontalBorder + col * cellSize));

            CellRenderer * cellRenderer = new CellRenderer();
            //TODO: Consider cell outline thickness
            cellRenderer->Update(cellSize, verticalBorder + col * cellSize + (col > 0 ? 1: 0), horizontalBorder + row * cellSize + (row > 0 ? 1: 0));
            cellRenderers.AddFirst(cellRenderer);
        }
    }

    Logger::Debug("Cell Size: " + std::to_string(cellSize));
    Logger::Debug("Vertical Boarder: " + std::to_string(verticalBorder));
    Logger::Debug("Horizontal Border: " + std::to_string(horizontalBorder));
}


