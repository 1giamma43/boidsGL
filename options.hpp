#ifndef OPTIONS_HPP
#define OPTIONS_HPP
#include "flock.hpp"
#include <iostream>

void setParameters(sf::RenderWindow &window, sf::RectangleShape &rect,
                   sf::Text &text, sf::Text &numText, sf::Font &font, float &Y,
                   std::string &label);
void draw(sf::RenderWindow &window, sf::RectangleShape &rect, sf::Text &text,
          sf::Text &numText);
template <typename T>
T insertParameters(sf::Event &ev, sf::RenderWindow &window,
                   sf::RectangleShape &rect, T &number,
                   sf::Text &usersNumText ) {
  if (rect.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,
                                      sf::Mouse::getPosition(window).y) &&
      ev.type == sf::Event::MouseButtonPressed &&
      ev.mouseButton.button == sf::Mouse::Left) {

    std::cout << "Insert number of boids between 0 and 30:\n ";
    std::cin >> number;
    usersNumText.setString(std::to_string(number));
    return number;
  }

  return number;
};

template <typename T>
T insertParameters( sf::RenderWindow &window,
                   sf::RectangleShape &rect, T &number,
                   sf::Text &usersNumText,std::string &message) {
    std::cout << message;
    std::cin >> number;
    usersNumText.setString(std::to_string(number));
    return number;
};
#endif