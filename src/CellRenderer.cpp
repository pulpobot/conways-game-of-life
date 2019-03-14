//
// Created by Santiago Alvarez Vargas on 2019-03-14.
//

#include "CellRenderer.h"

CellRenderer::CellRenderer()
{
    rectangle = sf::RectangleShape();
    Update(1, 1, 1);
}

void CellRenderer::Update(unsigned int cellSize, unsigned int x, unsigned int y)
{
    rectangle.setSize(sf::Vector2f(cellSize, cellSize));
    rectangle.setFillColor(DEFAULT_CELL_FILL_COLOR);
    rectangle.setOutlineColor(DEFAULT_CELL_BORDER_COLOR);
    rectangle.setOutlineThickness(DEFAULT_CELL_OUTLINE_THICKNESS);
    rectangle.setPosition(x, y);
}

void CellRenderer::Draw(sf::RenderWindow *window) const
{
    window->draw(rectangle);
}


