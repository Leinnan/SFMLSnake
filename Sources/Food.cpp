#include "Food.h"

#include <vector>
#include <SFML/Graphics.hpp>

Food::Food(sf::Vector2f start_pos, int point)
{
    points = point;
    graphic_object.setRadius(radius);
    graphic_object.setFillColor(sf::Color::Magenta);
    graphic_object.setPosition(start_pos);

    collision_object.setSize(sf::Vector2f(radius*2,radius*2));
    collision_object.setPosition(start_pos);
    //ctor
}

Food::~Food()
{
    //dtor
}
void Food::draw(sf::RenderWindow * app){
    ( * app ).draw(graphic_object);
}
sf::RectangleShape Food::getCollisionShape(){
    return collision_object;
}

void Food::setPosition(sf::Vector2f new_position){
    position = new_position;
    graphic_object.setPosition(position);
    collision_object.setPosition(position);

}
