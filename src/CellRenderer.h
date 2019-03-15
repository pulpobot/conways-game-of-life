//
// Created by Santiago Alvarez Vargas on 2019-03-14.
//

#ifndef CONWAYS_GAME_OF_LIFE_CELL_RENDERER_H
#define CONWAYS_GAME_OF_LIFE_CELL_RENDERER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class CellRenderer
{
private:
    inline const static sf::Color DEFAULT_CELL_FILL_ALIVE_COLOR = sf::Color(249, 223, 91);
    inline const static sf::Color DEFAULT_CELL_BORDER_ALIVE_COLOR = sf::Color(249, 223, 91);
    inline const static sf::Color DEFAULT_CELL_FILL_DEAD_COLOR = sf::Color(55, 10, 77);
    inline const static sf::Color DEFAULT_CELL_BORDER_DEAD_COLOR = sf::Color(55, 10, 77);
    sf::RectangleShape rectangle;
public:
    const static int OUTLINE_THICKNESS = 3;

    CellRenderer();
    ~CellRenderer() = default;
    void Update(unsigned int cellSize, unsigned int x, unsigned int y);
    void SetAlive();
    void SetDead();
    void Draw(sf::RenderWindow * window);
};


#endif //CONWAYS_GAME_OF_LIFE_CELL_RENDERER_H
