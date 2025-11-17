#include "options.hpp"
#include <iostream>

// capire perchè il template dava problemi
int insertParameters(sf::Event &ev, sf::RenderWindow &window,
                     sf::RectangleShape &rect, int &number,
                     sf::Text &usersNumText) {
  while (window.pollEvent(ev)) {

    if (rect.getGlobalBounds().contains(sf::Mouse::getPosition().x,
                                        sf::Mouse::getPosition().y) &&
        ev.type == sf::Event::MouseButtonPressed &&
        ev.mouseButton.button == sf::Mouse::Left) {

      std::cout << "Insert number of boids between 0 and 30:\n ";
      std::cin >> number;
      usersNumText.setString(std::to_string(number));
      return number;
    };
  }
  return number;
}

void setParameters(sf::RenderWindow &window, sf::RectangleShape &rect,
                   sf::Text &text, sf::Text &numText, sf::Font &font, float &Y, std::string &label) {
  
  rect.setSize({300.f, 40.f});
  rect.setFillColor(sf::Color(250, 200, 150));
  rect.setPosition(850.f, Y);
  font.loadFromFile("roboto/Roboto-Light.ttf");
  text.setFont(font);
  text.setString(label);
  text.setPosition(860.f, Y+10.f);
  text.setCharacterSize(17);
  text.setFillColor(sf::Color::Black);
  numText.setFont(font);
  numText.setPosition(1080.f, Y+10.f);
  numText.setCharacterSize(17);
  numText.setFillColor(sf::Color::Black);
}
