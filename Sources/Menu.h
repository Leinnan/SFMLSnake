#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


//! Menu class

//! Menu class contain Labels and is in basic the first
//! thing with which player can inte
//!
//!

class Menu
{
    public:
        Menu(sf::Vector2f start_pos);
        virtual ~Menu();
        void draw(sf::RenderWindow * app);
        void updatePositions();
        void updateState();
        void addNewOption(std::string label_text);
        void handleEvents();
        inline int getSelectedOption(){ return selected_option_nr;};
        sf::RectangleShape getMenuRectangle();
        void setCenteredToView(sf::View view, bool centered_in_x_axis = true,bool centered_in_y_axis = true);
        // ToDo
        // void setFont(std::string font_path);
    protected:
    private:
        std::vector < sf::Text > labels;
        int selected_option_nr = 0;
        int font_size = 35;
        bool is_visible = true;
        bool is_active = true;
        bool is_text_centered = true;
        sf::Font font_object;
        sf::Vector2f position;
        int options_padding = 5;
        int time_to_next_press = 10;
        //sf::Color selected_color(200,50,40,255);
        //sf::Color default_color(200,50,40,255);

};

#endif // MENU_H
