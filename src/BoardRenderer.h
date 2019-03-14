//
// Created by Santiago Alvarez Vargas on 2019-03-14.
//

#ifndef CONWAYS_GAME_OF_LIFE_BOARD_RENDERER_H
#define CONWAYS_GAME_OF_LIFE_BOARD_RENDERER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Board.h"
#include "common/utils/LinkedList.h"
#include "CellRenderer.h"

class BoardRenderer
{
private:


    sf::RenderWindow * window;
    Board * board;
    LinkedList<CellRenderer> cellRenderers; //TODO: Pool these

    bool isLandscape = true;
    unsigned int cellSize;
    unsigned int verticalBorder = 0;
    unsigned int horizontalBorder = 0;

    void CalculateCellSize();
public:
    BoardRenderer(Board * board, sf::RenderWindow * window);
    void Render();
};


#endif //CONWAYS_GAME_OF_LIFE_BOARD_RENDERER_H
