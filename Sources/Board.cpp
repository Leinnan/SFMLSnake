#include "Board.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "Snake.h"
#include "Arkona/Arkona.h"

using std::to_string;

Board::Board()
{


    srand( time( NULL ) );

    size_x = 20;
    size_y = size_x;
    tile_length = 20;
    border_box.setOutlineColor(sf::Color::Yellow);
    border_box.setFillColor(sf::Color(22,22,50,255));
    border_box.setOutlineThickness(2.f);
    foods.push_back(Food(sf::Vector2f(default_margin+50,default_margin+50),10));

    font_object.loadFromFile("Graphics/font.ttf");
    points_label.setFont(font_object);
    points_label.setString("New game");
    points_label.setCharacterSize(20);
    points_label.setColor(sf::Color::Yellow);

    this->recalculateBorderAndTexts();
}

Board::~Board()
{
    //dtor
}

void Board::recalculateBorderAndTexts(int view_width, int view_heigth){
    int base_width = 800;
    int base_height = 600;

    // dlugosc jest rowna bazowej dlugosci minus margines z lewej(domyslny) i prawej
    float result_width = base_width - default_margin - right_margin;
    // wysokosc jest rowna bazowej minus 2 razy margines domyslny(z gory i dolu)
    float result_height = base_height - default_margin - default_margin;
    border_box.setPosition(float(default_margin),float(default_margin));
    border_box.setSize(sf::Vector2f(result_width,result_height));

    float label_x = default_margin * 2 + result_width;
    float label_y = default_margin;

    points_label.setPosition(label_x, label_y);

}

void Board::updatePointsLabel(){
    points_label.setString("Points: " + to_string(player.getPoints()));
}

sf::Vector2f Board::generateNewFoodPosition(){

    bool is_colliding_with_player = true;
    float random_heigth = 0;
    float random_width = 0;

    std::vector < sf::Vector2f > player_positions = player.getPositions();
    while(is_colliding_with_player){
        is_colliding_with_player = false;
        random_width =( std::rand() % (int) (border_box.getSize().x) ) + (int) (border_box.getPosition().x);
        random_width = random_width - ( (int) (random_width) % 10);
        random_heigth =( std::rand() % (int) (border_box.getSize().y) ) + (int) (border_box.getPosition().y);
        random_heigth = random_heigth - ( (int) (random_heigth) % 10);

        for(sf::Vector2f part: player_positions){
            if(part.x == random_heigth && part.y == random_width)
                is_colliding_with_player = true;
                break;

        }
        std::cout << "x: " << random_width << "\ty:" << random_heigth << "\n";
    }
    return sf::Vector2f(random_width,random_heigth);
}


void Board::draw(sf::RenderWindow * app_pointer){

    ( * app_pointer ).draw(border_box);
    ( * app_pointer ).draw(points_label);
    for(auto food: foods){
        food.draw(app_pointer);
    }
    player.draw(app_pointer);
    // root.draw(app_pointer);
}

void Board::update(bool is_game_paused){
    player.handleEvents();
    if(frame_nr >= 10 && !is_game_paused){
        player.move(this->border_box);
        frame_nr = 0;

        // lets check is collision between player and food
        for(int i = 0; i < foods.size();i++){
            //
            if(ar::isCollisionBetweeenRectangles(player.getHeadRectangle(),foods[i].getCollisionShape())){
                // if is collision between them lets make our snake longer
                // add some points and update points label
                player.addNewPart();
                player.addPoints(foods[i].getPoints());
                updatePointsLabel();
                foods[i].setPosition(this->generateNewFoodPosition());
            }
        }
        this->updatePointsLabel();


    }

    if(!is_game_paused)
        frame_nr++;
}
