#include "Root.h"
#include <SFML/Graphics.hpp>

Root::Root()
{
    sf::Color darker_brown(22,22,50);
    sf::Color ligther_brown(189,154,100);
    for(int i = 0; i<=2;i++){
        root_parts[i].setPrimitiveType(sf::TrianglesStrip);
        root_parts[i].append(sf::Vector2f(10+i*10, 0));
        root_parts[i].append(sf::Vector2f(10+i*10, 10));
        root_parts[i].append(sf::Vector2f(20+i*10, 0));
        root_parts[i].append(sf::Vector2f(20+i*10, 10));
        root_parts[i][0].color = ligther_brown;
        root_parts[i][1].color = ligther_brown;
        root_parts[i][2].color = ligther_brown;
        root_parts[i][3].color = ligther_brown;
    }
    root_parts[0][0].color = darker_brown;
    root_parts[0][1].color = darker_brown;
    root_parts[2][2].color = darker_brown;
    root_parts[2][3].color = darker_brown;
    //ctor
    base_position.x = 50;
    base_position.y
      = 50;
    updatePositions();

}

Root::~Root()
{
    //dtor
}

void Root::updatePositions(){
    root_parts[0][0].position = base_position;
}

void Root::draw(sf::RenderWindow * app_pointer){

    ( * app_pointer ).draw(root_parts[0]);
    ( * app_pointer ).draw(root_parts[1]);
    ( * app_pointer ).draw(root_parts[2]);
}
