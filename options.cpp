#include "options.hpp"
#include <iostream>

void setParameters(sf::RenderWindow &window, sf::RectangleShape &rect,
                   sf::Text &text, sf::Text &numText, sf::Font &font, float &Y,
                   std::string &label) {

  rect.setSize({300.f, 40.f});
  rect.setFillColor(sf::Color(250, 200, 150));
  rect.setPosition(1050.f, Y);
  font.loadFromFile("roboto/Roboto-Light.ttf");
  text.setFont(font);
  text.setString(label);
  text.setPosition(1060.f, Y + 10.f);
  text.setCharacterSize(17);
  text.setFillColor(sf::Color::Black);
  numText.setFont(font);
  numText.setPosition(1280.f, Y + 10.f);
  numText.setCharacterSize(17);
  numText.setFillColor(sf::Color::Black);
}

void draw(sf::RenderWindow &window, sf::RectangleShape &rect, sf::Text &text,
          sf::Text &numText) {
  window.draw(rect);
  window.draw(text);
  window.draw(numText);
}
