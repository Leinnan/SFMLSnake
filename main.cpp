#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "Snake.h"
#include "Food.h"
#include "Menu.h"
#include "Board.h"




int main(){

    // Create the main window
    sf::RenderWindow app(sf::VideoMode(960, 540), "SFML window");
    app.setFramerateLimit(60);
    app.setMouseCursorVisible(false);

    sf::View view(sf::FloatRect(0,0,800,600));
    app.setView(view);

    int frame_number = 0;
    bool is_game_paused = false;
    bool is_game_started = false;

    Board game_board;

    Menu MainMenu(sf::Vector2f(10,10));
    MainMenu.addNewOption("Start game");
    MainMenu.addNewOption("Exit");
    MainMenu.setCenteredToView(view);

    sf::Texture background_texture;
    background_texture.loadFromFile("../Graphics/bg.png");

    sf::Sprite menu_background(background_texture);




    sf::Color green(22,200,35);

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::MouseLeft)
                is_game_paused = true;

            if (event.type == sf::Event::MouseEntered)
                is_game_paused = false;

            switch(event.key.code){
                case sf::Keyboard::Escape:
                    app.close();
                    break;
                case sf::Keyboard::Return:
                    if(!is_game_started){
                        switch(MainMenu.getSelectedOption()){
                            case 0:
                                is_game_started = true;
                                break;
                            case 1:
                                app.close();
                            default:
                                break;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        if(!is_game_started)
            MainMenu.handleEvents();
        else
            game_board.update(is_game_paused);


        app.clear();
        if(is_game_started)
            game_board.draw(&app);
        else{
            app.draw(menu_background);
            MainMenu.draw(&app);
        }
        // Update the window
        app.display();

        if(!is_game_paused){
            frame_number++;
        }
    }

    return EXIT_SUCCESS;
}
