#include "options.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

int main() {

  sf::RenderWindow window(sf::VideoMode({1200, 600}),
                          "simulation of a flock of boids");
  window.setPosition({300, 200});
  window.setFramerateLimit(15);

  //////////////////////////////////////////////////////
  sf::Font font;
  font.loadFromFile("roboto/Roboto-Light.ttf");
  ///////////////////////////////////////////////////

  sf::RectangleShape sfondo({400.f, 600.f});
  sfondo.setFillColor(sf::Color(0, 0, 0));
  sfondo.setPosition(800.f, 0.f);

  sf::RectangleShape modNBoids({300.f, 40.f});
  sf::Text usersText;
  sf::Text usersNumText;
  int numBoids = 1;
  modNBoids.setFillColor(sf::Color(250, 200, 150));
  modNBoids.setPosition(850.f, 0.f);
  usersText.setFont(font);
  usersText.setString("Number of boids--------->");
  usersText.setPosition(860.f, 10.f);
  usersText.setCharacterSize(17);
  usersText.setFillColor(sf::Color::Black);
  usersNumText.setFont(font);
  usersNumText.setPosition(1080.f, 10.f);
  usersNumText.setCharacterSize(17);
  usersNumText.setFillColor(sf::Color::Black);

  sf::RectangleShape dParam({300.f, 40.f});
  dParam.setFillColor(sf::Color(250, 200, 150));
  dParam.setPosition(850.f, 50.f);
  sf::Text usersText2;
  usersText2.setFont(font);
  usersText2.setString("Modify parameter d------>");
  usersText2.setPosition(860.f, 60.f);
  usersText2.setCharacterSize(17);
  usersText2.setFillColor(sf::Color::Black);
  sf::Text usersNumText2;
  usersNumText2.setFont(font);
  float dPar = 100.f;
  usersNumText2.setPosition(1080.f, 60.f);
  usersNumText2.setCharacterSize(17);
  usersNumText2.setFillColor(sf::Color::Black);

  sf::RectangleShape d_sParam({300.f, 40.f});
  d_sParam.setFillColor(sf::Color(250, 200, 150));
  d_sParam.setPosition(850.f, 100.f);
  sf::Text usersText3;
  usersText3.setFont(font);
  usersText3.setString("Modify parameter d_s---->");
  usersText3.setPosition(860.f, 110.f);
  usersText3.setCharacterSize(17);
  usersText3.setFillColor(sf::Color::Black);
  sf::Text usersNumText3;
  usersNumText3.setFont(font);
  float d_sPar = 5.f;
  usersNumText3.setPosition(1080.f, 110.f);
  usersNumText3.setCharacterSize(17);
  usersNumText3.setFillColor(sf::Color::Black);

  sf::RectangleShape sParam({300.f, 40.f});
  sParam.setFillColor(sf::Color(250, 200, 150));
  sParam.setPosition(850.f, 150.f);
  sf::Text usersText4;
  usersText4.setFont(font);
  usersText4.setString("Modify parameter s------>");
  usersText4.setPosition(860.f, 160.f);
  usersText4.setCharacterSize(17);
  usersText4.setFillColor(sf::Color::Black);
  sf::Text usersNumText4;
  usersNumText4.setFont(font);
  float sPar = 5.f;
  usersNumText4.setPosition(1080.f, 160.f);
  usersNumText4.setCharacterSize(17);
  usersNumText4.setFillColor(sf::Color::Black);

  sf::RectangleShape aParam({300.f, 40.f});
  aParam.setFillColor(sf::Color(250, 200, 150));
  aParam.setPosition(850.f, 200.f);
  sf::Text usersText5;
  usersText5.setFont(font);
  usersText5.setString("Modify parameter a------>");
  usersText5.setPosition(860.f, 210.f);
  usersText5.setCharacterSize(17);
  usersText5.setFillColor(sf::Color::Black);
  sf::Text usersNumText5;
  usersNumText5.setFont(font);
  float aPar = 0.9f;
  usersNumText5.setPosition(1080.f, 210.f);
  usersNumText5.setCharacterSize(17);
  usersNumText5.setFillColor(sf::Color::Black);

  sf::RectangleShape cParam({300.f, 40.f});
  cParam.setFillColor(sf::Color(250, 200, 150));
  cParam.setPosition(850.f, 250.f);
  sf::Text usersText6;
  usersText6.setFont(font);
  usersText6.setString("Modify parameter c------>");
  usersText6.setPosition(860.f, 260.f);
  usersText6.setCharacterSize(17);
  usersText6.setFillColor(sf::Color::Black);
  sf::Text usersNumText6;
  usersNumText6.setFont(font);
  float cPar = 5.f;
  usersNumText6.setPosition(1080.f, 260.f);
  usersNumText6.setCharacterSize(17);
  usersNumText6.setFillColor(sf::Color::Black);
  flock stormo;
  stormo.setFlockSize(numBoids);
  std::cout << "to start the simulation, please insert the parameters in the "
               "boxes on the right side of the window\n";

  std::vector<sf::Vector2f> posFlock = {{}};

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed) {
        window.close();
      }

      // capire perchè non funziona
      //ipotesi di soluzione: potrei toglierlo da qua e creare dentro la funzione direttamente il pollevent
      numBoids = insertParameters(modNBoids, event, numBoids, usersNumText);
        stormo.setFlockSize(numBoids);
      

        
      if (dParam.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,
                                            sf::Mouse::getPosition(window).y) &&
          event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {

        std::cout << "Insert number d parameter:\n "; // trovare valori di d
                                                      // possibili e modificare
        std::cin >> dPar;
        usersNumText2.setString(std::to_string(dPar));
      }
    }

    stormo.setInitVelocityF();
    stormo.collision();
    std::vector<sf::Vector2f> prevPosFlock = posFlock;
    posFlock = stormo.getPositionFlock();
    std::vector<sf::Vector2f> velocityFlock =
        stormo.getVelocityFlock(posFlock, prevPosFlock);

    stormo.moveFlock(d_sPar, dPar, sPar, aPar, cPar, posFlock, velocityFlock);

    window.clear(sf::Color(0, 226, 238));
    window.draw(sfondo);
    window.draw(modNBoids);
    window.draw(usersText);
    window.draw(usersNumText);
    window.draw(dParam);
    window.draw(usersText2);
    window.draw(usersNumText2);
    window.draw(d_sParam);
    window.draw(usersText3);
    window.draw(usersNumText3);
    window.draw(sParam);
    window.draw(usersText4);
    window.draw(usersNumText4);
    window.draw(aParam);
    window.draw(usersText5);
    window.draw(usersNumText5);
    window.draw(cParam);
    window.draw(usersText6);
    window.draw(usersNumText6);
    stormo.drawFlock(window);
    window.display();
  }
  return 0;
}