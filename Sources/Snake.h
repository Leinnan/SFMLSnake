#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SFML/Graphics.hpp>

//! Player class

//! The most important class in game.
//! This class contain all info about player and controll all his actions.
class Snake
{
    public:
        Snake(float start_pos_x = 20.f, float start_pos_y = 20.f);
        virtual ~Snake();
        void move(sf::RectangleShape border_box);
        void draw(sf::RenderWindow * app);
        void setDirection(int new_direction);
        void addNewPart();
        std::vector < sf::Vector2f >getPositions();
        bool isCollidingWithHimself();
        bool isCollidingWithPos(sf::Vector2f position);
        sf::RectangleShape getHeadRectangle();
        void handleEvents();
        void addPoints(int number);
        int getPoints();
        void resetVaules();
    protected:
    private:
        //!  direction

        //! 0- up
        //! 1- right
        //! 2- down
        //! 3- left
        int direction;
        int length_of_part = 10;
        sf::Color snake_color;
        std::vector < sf::Vector2f > parts;
        bool is_alive = true;
        int points = 0;

};

#endif // SNAKE_H
