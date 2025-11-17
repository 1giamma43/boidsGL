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
  sf::RectangleShape sfondo({400.f, 600.f});
  sfondo.setFillColor(sf::Color(0, 0, 0));
  sfondo.setPosition(800.f, 0.f);

  sf::RectangleShape modNBoids({500.f, 40.f});
  sf::Text usersText, usersNumText;
  int numBoids = 1;
  std::string label = "Number of boids--------->";
  float y = 0.f;
  setParameters(window, modNBoids, usersText, usersNumText, font, y, label);

  sf::RectangleShape dParam({300.f, 40.f});
  sf::Text usersText2, usersNumText2;
  float dPar = 100.f, y2 = 50.f;
  std::string label2 = "Modify parameter d------>";
  setParameters(window, dParam, usersText2, usersNumText2, font, y2, label2);

  sf::RectangleShape d_sParam({300.f, 40.f});
  sf::Text usersText3, usersNumText3;
  float d_sPar = 5.f, y3 = 100.f;
  std::string label3 = "Modify parameter d_s---->";
  setParameters(window, d_sParam, usersText3, usersNumText3, font, y3, label3);

  sf::RectangleShape sParam({300.f, 40.f});
  sf::Text usersText4, usersNumText4;
  float sPar = 5.f, y4 = 150.f;
  std::string label4 = "Modify parameter s------>";
  setParameters(window, sParam, usersText4, usersNumText4, font, y3, label3);

  sf::RectangleShape aParam({300.f, 40.f});
  sf::Text usersText5, usersNumText5;
  float aPar = 0.9f, y5 = 200.f;
  std::string label5 = "Modify parameter a------>";
  setParameters(window, aParam, usersText5, usersNumText5, font, y5, label5);

  sf::RectangleShape cParam({300.f, 40.f});
  sf::Text usersText6;
  sf::Text usersNumText6;
  float cPar = 5.f, y6 = 250.f;
  std::string label6 = "Modify parameter c------>";
  setParameters(window, cParam, usersText6, usersNumText6, font, y6, label6);

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
      // ipotesi di soluzione: potrei toglierlo da qua e creare dentro la
      // funzione direttamente il pollevent
      numBoids =
          insertParameters(event, window, modNBoids, numBoids, usersNumText);
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

    stormo.setInitVelocityF();// credo che questo vada messo dopo aver settato la dimensione dello stormo altrimenti ogni frame resetta le velocità
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