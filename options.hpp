#ifndef OPTIONS_HPP
#define OPTIONS_HPP
#include "flock.hpp"

int insertParameters(sf::Event &ev, sf::RenderWindow &window,
                     sf::RectangleShape &rect, int &number,
                     sf::Text &usersNumText);
void setParameters(sf::RenderWindow &window, sf::RectangleShape &rect,
                   sf::Text &text, sf::Text &numText,sf::Font &font, float &Y, std::string &label);

#endif