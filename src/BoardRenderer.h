//
// Created by Santiago Alvarez Vargas on 2019-03-14.
//

#ifndef CONWAYS_GAME_OF_LIFE_BOARD_RENDERER_H
#define CONWAYS_GAME_OF_LIFE_BOARD_RENDERER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Board.h"
#include "common/utils/LinkedList.h"
#include "CellRenderer.h"
#include "events/ConwaysEvents.h"

class BoardRenderer : public CellUpdatedEvent::CellUpdatedEventListener
{
private:


    sf::RenderWindow *window;
    Board *board;
    std::vector<std::vector<CellRenderer>> cellRenderers;

    bool isLandscape = true;
    int cellSize;
    int lateralBorder = 0;
    int longitudinalBorder = 0;

    void CalculateCellSize();

public:
    BoardRenderer(Board *board, sf::RenderWindow *window);
    virtual void OnCellUpdated(std::shared_ptr<Event> event);

    void Render();
};


#endif //CONWAYS_GAME_OF_LIFE_BOARD_RENDERER_H
