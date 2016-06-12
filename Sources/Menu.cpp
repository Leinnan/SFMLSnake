#include "Menu.h"
#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

Menu::Menu(sf::Vector2f start_pos)
{
    position.x = start_pos.x;
    position.y = start_pos.y;
    font_object.loadFromFile("Graphics/font.ttf");
}

Menu::~Menu()
{
    //dtor
}

void Menu::draw(sf::RenderWindow * app){
    if(!is_visible)
        return;

    //( * app ).draw(getMenuRectangle());
    for(sf::Text option: labels){

        ( * app ).draw(option);

    }

}
void Menu::addNewOption(std::string label_text){
    labels.push_back(sf::Text(label_text,font_object));
    labels.back().setCharacterSize(font_size);
    labels.back().setStyle(sf::Text::Regular);
    labels.back().setColor(sf::Color::Red);



    this->updatePositions();
    this->updateState();
}
//! For start method takes base position and move in x axis for padding.
//! Then repeat this for all Labels:
//! label_pos=updated_pos;
//! updated_pos.y += label font size and padding
void Menu::updatePositions(){
    sf::RectangleShape menu_rectangle = getMenuRectangle();
    sf::Vector2f updated_pos;
    updated_pos.x = position.x;
    updated_pos.y = position.y;
    std::cout << updated_pos.y << "\n";
    updated_pos.x += options_padding;

    for(int i = 0; i < labels.size(); i++){
        //if is centered x position looks like this
        // position = base_pos + (menu_size/2) -  (text_width/2)
        if(is_text_centered){
            updated_pos.x = position.x;
            updated_pos.x += menu_rectangle.getSize().x/2;
            updated_pos.x -= labels[i].getLocalBounds().width/2;
        }
        else{
            updated_pos.x = position.x + options_padding;
        }

        labels[i].setPosition(updated_pos);
        updated_pos.y += font_size;
        updated_pos.y += options_padding;

        //std::cout << updated_pos.y << "\t";
    }
    //std::cout << "\n";
}


void Menu::updateState(){

    for(int i = 0; i < labels.size(); i++){
        if(selected_option_nr == i){
            labels[i].setColor(sf::Color::Red);
        }
        else{
            labels[i].setColor(sf::Color::Green);
        }
    }
}

void Menu::handleEvents(){
    if(!is_active)
        return;

    if(time_to_next_press < 1){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            if(selected_option_nr <= 0)
                selected_option_nr = labels.size() - 1;
            else
                selected_option_nr--;
            this->updateState();
            time_to_next_press = 10;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            if(selected_option_nr >= labels.size() - 1)
                selected_option_nr = 0;
            else
                selected_option_nr++;
            this->updateState();
            time_to_next_press = 10;
        }
    }
    time_to_next_press--;
}


sf::RectangleShape Menu::getMenuRectangle(){
    sf::RectangleShape menu_rectangle;
    float rectangle_width = 0;
    float rectangle_height = 0;
    int longest_text_width = 0;
    for(int i = 0; i < labels.size(); i++){
        if(labels[i].getLocalBounds().width > longest_text_width)
            longest_text_width = labels[i].getLocalBounds().width;
        //std::cout << updated_pos.y << "\t";
    }
    // width is length of longest text and two options padding(from left and right)
    rectangle_width = options_padding * 2 + longest_text_width;
    // height is size of padding on top and bottom + (padding and font size) * text amount
    rectangle_height += options_padding * 2;
    rectangle_height += (options_padding + font_size) * labels.size();

    menu_rectangle.setPosition(position);
    menu_rectangle.setSize(sf::Vector2f(rectangle_width,rectangle_height));

    return menu_rectangle;

}

void Menu::setCenteredToView(sf::View view, bool centered_in_x_axis, bool centered_in_y_axis){
    sf::RectangleShape viewShape(view.getSize());
    sf::RectangleShape menu_rectangle = getMenuRectangle();

    if(centered_in_x_axis){
        position.x = viewShape.getSize().x / 2;
        std::cout << position.x << "\t";
        position.x -= menu_rectangle.getSize().x / 2;
        std::cout << position.x << "\t";
    }

    if(centered_in_y_axis){
        position.y = viewShape.getSize().y / 2;
        std::cout << position.x << "\t";
        position.y -= menu_rectangle.getSize().y / 2;
        std::cout << position.x << "\n";
    }
    this->updatePositions();

}
