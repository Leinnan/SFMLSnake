#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Snake.h"
#include "Food.h"
#include "Root.h"

class Board
{
    public:
        Board();
        virtual ~Board();
        void recalculateBorderAndTexts(int view_width = 800, int view_height = 600);
        void draw(sf::RenderWindow * app);
        void update(bool is_game_paused = false);
        void updatePointsLabel();
        sf::Vector2f generateNewFoodPosition();
    protected:
    private:
        int size_x;
        int size_y;
        int tile_length;
        Snake player;
        sf::RectangleShape border_box;
        int default_margin = 10;
        int right_margin = 300;
        std::vector < Food > foods;
        sf::Font font_object;
        sf::Text points_label;
        int frame_nr = 0;
        Root root;

};

#endif // BOARD_H
