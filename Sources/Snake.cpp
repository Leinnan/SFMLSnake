#include "Snake.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Arkona/Arkona.h>



Snake::Snake(float start_pos_x, float start_pos_y){
    parts.push_back(sf::Vector2f(start_pos_x+length_of_part,start_pos_y+length_of_part));
    direction = 2;
    snake_color.r = 20;
    snake_color.g = 200;
    snake_color.b = 35;
}

Snake::~Snake()
{
    //dtor
}
void Snake::setDirection(int new_direction){
    /* nowy kierunek nie moze byc przeciwny do obecnego
    jesli odejmiemy liczbe odpowiadajaca kierunkowi
    od liczby odpowiadajacej kierunkowi przeciwnemu
    widac, ze zawsze wyjdzie liczba parzysta, stad wynik:
    (direction - new direction) % 2 == 0 */

    if(std::abs(direction - new_direction) % 2 == 1){
        direction = new_direction;
    }
}
void Snake::addNewPart(){
    sf::Vector2f last_pos(0,0);
    this->parts.push_back(parts[parts.size()-1]);
}

void Snake::move(sf::RectangleShape border_box){

    if(!is_alive)
        return;
    //jesli jest wiecej niz jeden klocek kazdy kolejny ustawiamy w miejscu poprzedniego

    if(parts.size() > 1 ){
        // dodaje modyfikator ktory bedzie zmienial
        // znak w zaleznosci od tego czy dany element ma byc przed
        // czy tez za poprzednim elementem
        int modifier = 1;
        //
        //std::cout << ar::distanceBetweenVector2f(parts[1], parts[0]) << "\n";
        for(int i = parts.size() - 1; i >= 1; i--){
           parts[i] = parts[i-1];

        }
    }

    //w zaleznosci od kierunku przesuwamy pierwszy klocek o okreslona odleglosc
    switch(direction){
        case 0:
            parts[0].y -= length_of_part;
            break;
        case 1:
            parts[0].x += length_of_part;
            break;
        case 2:
            parts[0].y += length_of_part;
            break;
        case 3:
            parts[0].x -= length_of_part;
    }

    if(!ar::isRectangleInsideRectangle(this->getHeadRectangle(),border_box)){
        switch(direction){
            case 0:
                parts[0].y = border_box.getPosition().y + border_box.getSize().y - length_of_part;
                break;
            case 1:
                parts[0].x = border_box.getPosition().x;
                break;
            case 2:
                parts[0].y = border_box.getPosition().y;
                break;
            case 3:
                parts[0].x = border_box.getPosition().x + border_box.getSize().x - length_of_part;
        }
    }

    if(isCollidingWithHimself())
        this->resetVaules();

}

void Snake::draw(sf::RenderWindow * app){
    bool is_first = true;
    for(sf::Vector2f part: parts){
        sf::RectangleShape snakebox;
        // first part has other color than rest
        if(is_first){
            snakebox.setFillColor(sf::Color(200,40,30,255));
            is_first = false;
        }
        else{
            snakebox.setFillColor(snake_color);
            snakebox.setOutlineColor(sf::Color(0,0,0,255));
            snakebox.setOutlineThickness(1.f);
        }
        snakebox.setSize(sf::Vector2f(length_of_part-2,length_of_part-2));
        snakebox.setPosition(part.x+1,part.y+1);
        ( * app ).draw(snakebox);
    }
}

std::vector < sf::Vector2f > Snake::getPositions(){
    return parts;
}

bool Snake::isCollidingWithHimself(){
    bool result = false;
    if(parts.size() > 2 ){
        //sprawdzamy czy kazdy(poza pierwszym) element
        //ma pozycje taka sama jak pierwszy element
        //jesli tak zaszla kolizja
        for(int i = parts.size() - 1; i >= 1; i--){
            if(parts[i].x == parts[0].x && parts[i].y == parts[0].y){
                result = true;
            }
        }
    }
    return result;
}

bool Snake::isCollidingWithPos(sf::Vector2f position){
    bool result = false;
//! todo
    return result;
}

sf::RectangleShape Snake::getHeadRectangle(){
    sf::RectangleShape snakebox;
    snakebox.setSize(sf::Vector2f(length_of_part-2,length_of_part-2));
    snakebox.setPosition(parts[0]);

    return snakebox;
}

void Snake::handleEvents(){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->setDirection(0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->setDirection(2);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->setDirection(3);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->setDirection(1);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
        this->addNewPart();
    }
}


int Snake::getPoints(){
    return points;
}
void Snake::addPoints(int number){
    points+=number;
}

void Snake::resetVaules(){
        this->~Snake();
        new (this) Snake;
}
