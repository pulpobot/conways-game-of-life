//
// Created by Santiago Alvarez Vargas on 2019-03-14.
//

#include "CellRenderer.h"

CellRenderer::CellRenderer()
{
    rectangle = sf::RectangleShape();
    rectangle.setOutlineColor(DEFAULT_CELL_BORDER_DEAD_COLOR);
    rectangle.setOutlineThickness(OUTLINE_THICKNESS);
    Update(OUTLINE_THICKNESS * 2, 1, 1);
    SetDead();
}

void CellRenderer::Update(unsigned int cellSize, unsigned int x, unsigned int y)
{
    //Consider cell outline thickness by reducing from the cell size
    rectangle.setSize(sf::Vector2f(cellSize - OUTLINE_THICKNESS * 2, cellSize - OUTLINE_THICKNESS * 2));
    rectangle.setPosition(x, y);
}


void CellRenderer::Draw(sf::RenderWindow *window)
{
    window->draw(rectangle);
}

void CellRenderer::SetDead()
{
    rectangle.setFillColor(DEFAULT_CELL_FILL_DEAD_COLOR);
    rectangle.setOutlineColor(DEFAULT_CELL_BORDER_DEAD_COLOR);
}

void CellRenderer::SetAlive()
{
    rectangle.setFillColor(DEFAULT_CELL_FILL_ALIVE_COLOR);
    rectangle.setOutlineColor(DEFAULT_CELL_BORDER_ALIVE_COLOR);
}


