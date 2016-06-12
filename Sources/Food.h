#ifndef FOOD_H
#define FOOD_H

#include <vector>
#include <SFML/Graphics.hpp>


class Food
{
    public:
        Food(sf::Vector2f start_pos, int point);
        void draw(sf::RenderWindow * app);
        virtual ~Food();
        sf::RectangleShape getCollisionShape();
        inline int getPoints(){ return points; };
        void setPosition(sf::Vector2f new_position);
    protected:
    private:
        sf::Vector2f position;
        sf::CircleShape graphic_object;
        sf::RectangleShape collision_object;
        int radius = 4;
        int points = 1;
};

#endif // FOOD_H
