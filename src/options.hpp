#ifndef OPTIONS_HPP
#define OPTIONS_HPP
#include "flock.hpp"
#include <iostream>

template <typename T>
void setParameters(sf::RenderWindow &window, sf::RectangleShape &rect,
                   sf::Text &paramText, sf::Text &paramNumText, sf::Font &font,
                   const float positionRect, std::string &label, T par) {
  rect.setSize({300.f, 40.f});
  rect.setFillColor(sf::Color(250, 200, 150));
  rect.setPosition(1050.f, positionRect);
  font.loadFromFile("roboto/Roboto-Light.ttf");
  paramText.setFont(font);
  paramText.setString(label);
  paramText.setPosition(1060.f, positionRect + 10.f);
  paramText.setCharacterSize(17);
  paramText.setFillColor(sf::Color::Black);
  paramNumText.setFont(font);
  paramNumText.setPosition(1250.f, positionRect + 10.f);
  paramNumText.setCharacterSize(17);
  paramNumText.setFillColor(sf::Color::Black);
  paramNumText.setString(std::to_string(par));
};

template <typename T>
T changeParameters(sf::Event &ev, sf::RenderWindow &window,
                   sf::RectangleShape &rect, T &par, sf::Text &paramNumText,
                   std::string &terminalText) {
  if (rect.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,
                                      sf::Mouse::getPosition(window).y) &&
      ev.type == sf::Event::MouseButtonPressed &&
      ev.mouseButton.button == sf::Mouse::Left) {

    std::cout << terminalText << "\n";
    std::cin >> par;
    paramNumText.setString(std::to_string(par));
    return par;
  }

  return par;
};

void draw(sf::RenderWindow &window, sf::RectangleShape &rect,
          sf::Text &paramText, sf::Text &paramNumText) {
  window.draw(rect);
  window.draw(paramText);
  window.draw(paramNumText);
};
#endif