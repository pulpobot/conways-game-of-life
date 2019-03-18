//
// Created by Santiago Alvarez Vargas on 2019-03-14.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include "BoardRenderer.h"
#include "common/utils/Logger.h"
#include "common/event/EventSystem.h"

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

    EventSystem::Instance().AddListener((CellUpdatedEvent::CellUpdatedEventListener *) this);

    //TODO: I would like to be able to change the size through a debug menu, listen to events here
}

void BoardRenderer::Render()
{
    for (int row = 0; row < board->rows; ++row)
    {
        for (int col = 0; col < board->columns; ++col)
        {
            cellRenderers[row][col].Draw(window);
        }
    }
}

void BoardRenderer::CalculateCellSize()
{
    // The board is generated based on whenever the device is on portrait or landscape mode
    // We ensure we accommodate the amount of cells expected in the board

    //Calculate the size of a cell based on the width of the screen, and consider the fact that outlines between cells overlap
    cellSize = ((window->getSize().x + (board->columns - 1) * CellRenderer::OUTLINE_THICKNESS)) /
               (double) (board->columns);

    int boardWidth = ((cellSize - CellRenderer::OUTLINE_THICKNESS) * board->columns) + CellRenderer::OUTLINE_THICKNESS;
    int boardHeight = ((cellSize - CellRenderer::OUTLINE_THICKNESS) * board->rows) + CellRenderer::OUTLINE_THICKNESS;
    //leave some lateral and longitudinal borders so we center the cells if the don't occupy the entire space
    lateralBorder = (window->getSize().x - (boardWidth)) / 2;
    longitudinalBorder = (window->getSize().y - (boardHeight)) / 2;

    //if the amount of columns can't fit in the width of the screen, recalculate based on the rows and height instead
    if (cellSize - CellRenderer::OUTLINE_THICKNESS * 2 <= 0 || window->getSize().y < boardHeight)
    {
        Logger::Debug("ain't gonna fit! Resizing with height instead");
        cellSize =
                ((window->getSize().y + (board->rows - 1) * CellRenderer::OUTLINE_THICKNESS)) / (double) (board->rows);
        boardWidth = ((cellSize - CellRenderer::OUTLINE_THICKNESS) * board->columns) + CellRenderer::OUTLINE_THICKNESS;
        boardHeight = ((cellSize - CellRenderer::OUTLINE_THICKNESS) * board->rows) + CellRenderer::OUTLINE_THICKNESS;
        lateralBorder = (window->getSize().x - (boardWidth)) / 2;
        longitudinalBorder = (window->getSize().y - (boardHeight)) / 2;

        //something went really wrong with that board configuration if this passes
        if (cellSize - CellRenderer::OUTLINE_THICKNESS * 2 <= 0 || window->getSize().x < boardWidth)
        {
            Logger::Error("Can't fit that many cells");
            throw "Can't fit that many cells";
        }
    }

    cellRenderers.clear();

    for (int row = 0; row < board->rows; ++row)
    {
        cellRenderers.emplace_back(std::vector<CellRenderer>());
        for (int col = 0; col < board->columns; ++col)
        {
            //size border + size of the cell + thickness if col 0 or reduce the thickness if > 0, so the outlines overlap
            cellRenderers[row].emplace_back(CellRenderer());
            cellRenderers[row][col].Update
                    (cellSize,
                     lateralBorder + col * cellSize - ((col - 1) * CellRenderer::OUTLINE_THICKNESS),
                     longitudinalBorder + row * cellSize - ((row - 1) * CellRenderer::OUTLINE_THICKNESS));
        }
    }

}

void BoardRenderer::OnCellUpdated(std::shared_ptr<Event> event)
{
    CellUpdatedEvent *cellUpdatedEvent = (CellUpdatedEvent *) event.get();
    if (cellUpdatedEvent->alive)
    {
        cellRenderers[cellUpdatedEvent->row][cellUpdatedEvent->col].SetAlive();
    }
    else
    {
        cellRenderers[cellUpdatedEvent->row][cellUpdatedEvent->col].SetDead();
    }
}


