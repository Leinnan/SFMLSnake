#ifndef ROOT_H
#define ROOT_H

#include <SFML/Graphics.hpp>
#include <array>


class Root
{
    public:
        Root();
        virtual ~Root();
        inline void setOrientation(int new_direction){ orientation = new_direction % 2; this->updatePositions();};
        inline void setBasePosition(sf::Vector2f new_pos){ base_position = new_pos; this->updatePositions();};
        void updatePositions();
        void draw(sf::RenderWindow * app);
    protected:
    private:
        //! three vertex array, the middle one for the place where player can go below root
        //! and rest for the start and end of the root
        std::array< sf::VertexArray, 3 > root_parts;
        sf::Vector2f base_position;
        int length_of_part = 10;
        //! 0=horizontal
        //! 1=vertical
        int orientation = 0;
};

#endif // ROOT_H
