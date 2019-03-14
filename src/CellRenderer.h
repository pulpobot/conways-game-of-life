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
    inline const static sf::Color DEFAULT_CELL_BORDER_COLOR = sf::Color::Black;
    inline const static sf::Color DEFAULT_CELL_FILL_COLOR = sf::Color::White;
    const static unsigned int DEFAULT_CELL_OUTLINE_THICKNESS = 3;
    sf::RectangleShape rectangle;
public:
    CellRenderer();
    ~CellRenderer() = default;
    void Update(unsigned int cellSize, unsigned int x, unsigned int y);
    void Draw(sf::RenderWindow * window) const;
};


#endif //CONWAYS_GAME_OF_LIFE_CELL_RENDERER_H
